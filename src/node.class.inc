<?php

// simple base class for accessing Drupal node fields

// phase I: goal is read only node object that simplifies field access so that all 
// index checking and error handling is hidden from caller and 'reasonable' results are
// always returned, regardless of field initialization status/existance, etc.

// main features of this class is to load node and provide a get method that can be used
// for all fields of the underlying node


class nodeClass {
  
  protected $node = NULL;

  public function __construct($node) { 
    if ($node > 0)
      $this->node = node_load($node);  // handle node id
    if ($node && is_object($node))
      $this->node = $node; 
    if (!$node) 
      $node = (object) array_fill_keys(array('nid', 'vid', 'type', 'uid', 'title', 'status', 'language', 'created', 'changed', 'promote', 'sticky', 'og', 'tnid', 'comment', 'translate', 'revision_timestamp', 'revision_uid', 'data'), NULL);
  } // ctor
  
  public function toString() { 
    return var_export($this->node, 1); 
  } // toString
  
  // not used
  /*
  protected function out($obj) { 
    return is_string($obj) ? $obj : var_export($obj, 1); 
  }
  */

  // assumption: multifields and lists of multifields one level deep
  // eg. $node->field->subfield or $node->field can be lists or multis but no deeper
  // null $ndx means return all items as array if more than one, otherwise return scalar
  // return object for multivalue when subfield is null
  public function get($fieldname, $retval = null, $ndx = null, $subfieldname = null) {
    
    // check that $this->node is valid
    if (!($this->node && $this->node->type))
      return $retval;
    
    // TODO: allow passing keys with this array as default
    $keys = array('nid', 'uid', 'tid', 'value');
    
    if (!($this->node && isset($this->node->{$fieldname}))) 
      return $retval;
    
    $field = $this->node->{$fieldname};
    
    // scalar, e.g. 'title' or 'type'
    if ($field && !is_array($field))
      return $field;
    
    // not a valid field
    if (!($field && is_array($field) && array_key_exists(LANGUAGE_NONE, $field) && is_array($field[LANGUAGE_NONE]))) 
      return "ret - 1"; // $retval;      
    
    // if $ndx present, check validity
    if (!(is_null($ndx) || array_key_exists($ndx, $field[LANGUAGE_NONE])))
      return $retval; // "ret - 2";    
    
    // check if $fieldname[LANGUAGE_NONE][0] is a scalar
    if (!is_array($field[LANGUAGE_NONE][0]))
      return $field[LANGUAGE_NONE][0] . "-yyy";  
    
    // if not a list, multi if $fieldname[LANGUAGE_NONE][0] keys have 'id' or 'field_...'
    // if a list, multi if all $fieldname[LANGUAGE_NONE][$ndx] keys have 'id' or 'field_...'
    // so just test [0]
    // TODO: extend test to look for at least one 'field_*' element?
    $is_multi = array_key_exists('id', $field[LANGUAGE_NONE][0]);
      
    $cnt = count($field[LANGUAGE_NONE]);
    // this is not a good enough test, 
    // e.g., what if only 1 item in unlimited list?  
    // TODO: rename to $has_list?
    // looks like we need meta data
    $is_list = $cnt > 1; 
    
    
    
  // Drupal  API calls 
    $fields = field_info_extra_fields('node', $this->node->type, 'form');
    $fields += field_info_instances('node', $this->node->type);     
    
    
    if ($is_list && is_null($ndx))
      $fielditem = $field[LANGUAGE_NONE];
    else {
      $i = is_null($ndx) ? 0 : $ndx;
      if (is_array($field[LANGUAGE_NONE]) && array_key_exists($i, $field[LANGUAGE_NONE]))      
        $fielditem = $field[LANGUAGE_NONE][$i];
      else
        return "ret - 5"; // todo - list with one element? ???
    }
    
    // check if $fielditem is a string
    if (!is_array($fielditem))
      return $fielditem . "-xxx";    
    
    // test for subfield name
    if ($subfieldname && !array_key_exists($subfieldname, $fielditem))
      return "ret - 3"; //$retval;      
      
    // TODO: return actual values
    if ($is_list) {
      $arr = array();
      if (is_null($ndx))
        if ($is_multi) {
          foreach($fielditem as $key => $value) {

            // check for subfield, else return all fields
            if (is_null($subfieldname))
              if (array_key_exists($subfieldname, $value))
                return $retval;
              $v = $value[];
            else
              $v = "object goes here)"; // TODO:
            $arr[$key] = $v; 
          }
          return $arr; // "array of objects";
        }
        else {
          foreach($fielditem as $key => $value)
            $arr[$key] = $value;
          return $arr; // "array of scalars";
        }
      else
        if ($is_multi) {
          
          // check for subfield, else return all fields
          
          return $fielditem[$ndx]; // more to do?
          //return "array element, object";
        }
        else {
          return $fielditem[$ndx];
          //return "array element, scalar";
        }
    }
    else {
      if ($is_multi)
        // check for subfield, else return all fields  
      
        return "multi object";
      else {   
        foreach ($keys as $key)
          if (array_key_exists($key, $fielditem))
            return $fielditem[$key];  // call get again?
          
        // todo: not a known key?
        return "ret - 7"; // $fielditem; // "scalar"; uid, val etc
      }
    } // not $is_list

    
    /*
    if (!$subfieldname) {
      
         // return array of of values if list, possibly empty
         // return object with properties if multi 
         // return scalar if not multi and not list
      
      // search for likely keys
      foreach ($keys as $key)
        if (array_key_exists($key, $fielditem))
          return $fielditem[$key];  // call get again?
      return $retval;
    } // $subfieldname

    if (is_array($fielditem) && array_key_exists($subfieldname, $fielditem)) {
      //if ($subfieldname == 'field_project_subject_email') 
      //print "in a subfield\n";
      $subfield = $field[LANGUAGE_NONE][$ndx][$subfieldname];
 
      if ($subfield && is_array($subfield) && array_key_exists(LANGUAGE_NONE, $subfield) &&   is_array($subfield[LANGUAGE_NONE]) && array_key_exists(0, $subfield[LANGUAGE_NONE])) {
        $subfielditem = $subfield[LANGUAGE_NONE][0];
        // search for likely keys
        foreach ($keys as $key)
          if (array_key_exists($key, $subfielditem))
            return $subfielditem[$key];  // call get again?
        
      } else {
         // return array of of values if not multi
         // return array of array of all multi values indexed by subfieldname
      }
    } // 
    
    */
    
    return "ret - last"; //$retval;      
  } // get()


} // nodeClass

