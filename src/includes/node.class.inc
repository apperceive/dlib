<?php

// simple base class for accessing Drupal node fields

// phase I: goal is read only node object that simplifies field access so that all 
// index checking and error handling is hidden from caller and 'reasonable' results are
// always returned, regardless of field initialization status/existance, etc.

// main features of this class is to load node and provide a get method that can be used
// for all fields of the underlying node


class nodeClass {
  
  public $node = NULL;
  
  // private?
  protected $keys = array('nid', 'uid', 'tid', 'value');

  public function __construct($node) { 
    if ($node > 0)
      $node = node_load($node);  // handle node id
    if ($node && is_object($node))
      $this->node = $node; 
    if (!$node) 
      $node = (object) array_fill_keys(array('nid', 'vid', 'type', 'uid', 'title', 'status', 'language', 'created', 'changed', 'promote', 'sticky', 'og', 'tnid', 'comment', 'translate', 'revision_timestamp', 'revision_uid', 'data'), NULL);
  } // ctor
  
  public function toString() { 
    return var_export($this->node, 1); 
  } // toString

  // TODO: make this protected?
  // assumption: multifields and lists of multifields one level deep
  // eg. $node->field->subfieldname or $node->field can be lists or multis but no deeper
  // null $ndx means return all items as array if more than one, otherwise return scalar
  // return object for multivalue when subfieldname is null
  public function get($fieldname, $retval = null, $ndx = null, $subfieldname = null) {
    
    // check that $this->node is valid
    if (!($this->node && $this->node->type))
      return $retval;
    
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
    //$fields = field_info_extra_fields('node', $this->node->type, 'form');
    //$fields += field_info_instances('node', $this->node->type);     
    
    if ($is_list && is_null($ndx))
      $fielditem = $field[LANGUAGE_NONE];
    else {
      $i = is_null($ndx) ? 0 : $ndx;
      if (is_array($field[LANGUAGE_NONE]) && array_key_exists($i, $field[LANGUAGE_NONE]))      
        $fielditem = $field[LANGUAGE_NONE][$i];
      else
        return "ret - 555"; // todo - list with one element? ???
    }
    
    // check if $fielditem is a string
    if (!is_array($fielditem))
      return $fielditem . "-xxx";    
    
    //if ("field_project_observer_email" == $subfieldname)
    //  var_dump($fielditem);     
    

    // test for subfieldname
    //if ($subfieldname && !array_key_exists($subfieldname, $fielditem))
    //  return $retval;
    
    // TODO: return actual values
    if ($is_list) {
      $arr = array();        
      if (is_null($ndx)) {
        if ($is_multi) {
          foreach($fielditem as $key => $value) {   
            $arr[$key] = $this->get_obj_or_value($value, $subfieldname, NULL); 
            // return object?
          }
          return $arr; // "array of objects";
        }
        else {
          foreach($fielditem as $key => $value)
            $arr[$key] = $value;
          return $arr; // "array of scalars";
        }
      }
      else {

        if (array_key_exists($ndx, $fielditem))
            $fielditem = $subfieldname[$ndx];
        else if (array_key_exists($ndx, $fielditem))
            $fielditem = $fielditem[$ndx];
        return $this->get_obj_or_value($fielditem, $subfieldname, $retval);
      }
        /*
        if ($is_multi) {
          return $this->get_obj_or_value($fielditem[$ndx], $subfieldname, $retval);
          //return "array element, object";
        }
        else {
          return $this->get_obj_or_value($fielditem[$ndx], $subfieldname, $retval);
          //return "array element, scalar";
        }
        */
    }
    else {
      
       //if ("field_project_observer_email" == $fieldname)
     //   var_dump($fielditem);     


        
      if ($is_multi) {
        //var_dump($this->get_obj_or_value($fielditem, $subfieldname, $retval));
        return $this->get_obj_or_value($fielditem, $subfieldname, $retval);
        //return "multi object";
      }
      else {         
        // get_objs_or_values   
        $d = $this->check_keys($fielditem, $retval);
        if (!($d === $retval))
          return $d;
           
        //foreach ($this->keys as $key)
         // if (array_key_exists($key, $fielditem))
         //   return $this->get_obj_or_value($fielditem[$key], $subfieldname, $retval); 
          
        // todo: not a known key?
        return "ret - 777"; // $fielditem; // "scalar"; uid, val etc
      }
    } // not $is_list

    return "ret - LAST"; //$retval;      
  } // get()

  
  // not used?
  // get array or singleton of objects or values
  /*
  public function get_objs_or_values($data = array(), $fname = NULL, $retval = NULL) {
    
    // return single object
    if (is_array($data) && array_key_exists(0, $data) && count($data) == 1) {
      $data = $data[0];
      $arr = array('aaa' => 'aaa');
      foreach ($data as $key => $value)
        $arr[$key] = $this->get_obj_or_value($value);
      return $arr;
    }
    
    // return array of objects
    if (is_array($data) && array_key_exists(0, $data) && count($data) > 1) {
      $arr2 = array('ggg' => 'ggg');
      foreach ($data as $ndx => $d) {
        $arr = array();
        foreach ($data as $key => $value)
          $arr[$key] = $this->get_obj_or_value($value);
        $arr2[$ndx] = $arr;
      }
      return $arr2;      
    }
    return $retval;
  } // get_objs_or_values
  */
  
  // private?
  // get an object or value in something of the form $f[LANGUAGE_NONE][0]['keyname']
  // return the value associated with key name if supplied or one of 'nid', 'uid', etc
  // otherwise return entire endpoint as an array, indexed by fieldname
  public function get_obj_or_value($data, $fieldname = NULL, $retval = NULL) {
    
    if (!(is_array($data) || is_object($data)))
      return $data;  // scalar
    
    if (is_object($data))
      return (array) $data;
    
    if (is_array($data) && array_key_exists(LANGUAGE_NONE, $data))
      $data = $data[LANGUAGE_NONE];
      
    if (is_array($data) && !is_null($fieldname) && array_key_exists($fieldname, $data)) {
      $data = $data[$fieldname];
      if (is_array($data) && array_key_exists(LANGUAGE_NONE, $data))
        $data = $data[LANGUAGE_NONE];
      if (is_array($data) && array_key_exists(0, $data))
        $data = $data[0]; 
      if (is_array($data) && array_key_exists('value', $data))
        $data = $data['value']; 
      
      $d = $this->check_keys($data, $retval);
      if (!($d === $retval)) 
        return $d;

      //if ("field_project_subject_email" == $fieldname)
      //  var_dump($data);
     return $data;  // may be an array[und][0][?}
    }
  
    if (is_array($data) && array_key_exists(0, $data))
      $data = $data[0];
    
    $d = $this->check_keys($data, $retval);
    if (!($d === $retval))
      return $d;
      
    if (is_array($data) && !is_null($fieldname) && array_key_exists(fieldname, $data))
      return $data[$fieldname];

    // return object with field names or array
    
    if (is_null($fieldname)) {
      $arr = array();
      if (is_array($data)) {
        foreach ($data as $key => $value) {
          if ($this->is_drupal_object($value))
            $arr[$key] = $value[LANGUAGE_NONE][0]['value'];
          else
            $arr[$key] = $value;
        }
        return $arr;
      }
      else 
        return $data;
    } // null fieldname
    
    
    return $retval;
  } // $this->get_obj_or_value
  
  // private
  public function check_keys($data, $retval = NULL) {
    if (!is_null($data) && is_array($data)) {
      foreach ($this->keys as $key)
        if (array_key_exists($key, $data))
          return $data[$key]; 
    }
    return $retval;
  } //check_keys
  
  // private
  public function is_drupal_object($value) {
     return is_array($value) && array_key_exists(LANGUAGE_NONE, $value) && is_array($value[LANGUAGE_NONE]) && array_key_exists(0, $value[LANGUAGE_NONE]) && is_array($value[LANGUAGE_NONE][0]) && array_key_exists('value', $value[LANGUAGE_NONE][0]);
  } // is_drupal_object
  
  // protected
  public function out($obj) { 
    return is_string($obj) ? obj : var_export($obj, 1); 
  }


} // nodeClass

