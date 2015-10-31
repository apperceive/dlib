<?php

// drupal calls here
//
//

class nodeClass {
  
  protected $node = NULL;

  public function __construct($node) { 
    if ($node > 0)
      $this->node = node_load($node);
    if ($node && is_object($node))
      $this->node = $node; 
  }
  
  public function toString() { 
    return var_export($this->node, 1); 
  }
  
  protected function out($obj) { 
    return is_string($obj) ? $obj : var_export($obj, 1); 
  }

  // assumption: multifields and lists of multifields one level deep
  // eg. $node->field->subfield or $node->field can be lists or multis but no deeper
  // null $ndx means return all items as array if more than one, otherwise return scalar
  // return object for multivalue when subfield is null
  public function get($fieldname, $retval = 0, $ndx = null, $subfieldname = null) {
    
    // TODO: allow passing keys with this array as default
    $keys = array('nid', 'uid', 'tid', 'value');
    
    if (!$this->node || !isset($this->node->{$fieldname})) 
      return $retval;
    
    $field = $this->node->{$fieldname};
    
    // scalar
    if ($field && !is_array($field))
      return $field;
    
    // not a valid field
    if (!($field && is_array($field) && array_key_exists(LANGUAGE_NONE, $field) && is_array($field[LANGUAGE_NONE]))) 
      return $retval;      
    
    // if $ndx present, check validity
    if (is_null($ndx) && !array_key_exists($ndx, $field[LANGUAGE_NONE]))
      return $retval;
    
    $cnt = count($field[LANGUAGE_NONE]);
    $is_list = $cnt > 1;
    // if not a list, multi if $fieldname[LANGUAGE_NONE][0] keys have form id or field_...
    // if a list, multi if all $fieldname[LANGUAGE_NONE][$ndx] keys have form id or field_...
    // so just test [0]
    // extend test to look for at least one 'field_*' element?
    $is_multi = array_key_exists('id', $fieldname[LANGUAGE_NONE][0]);
      
    if ($is_list && is_null($ndx))
      $fielditem = $field[LANGUAGE_NONE];
    else
      $fielditem = $field[LANGUAGE_NONE][$ndx];
    
    // test for subfield name
    if ($subfieldname && !array_key_exists($subfilename, $fieldname))
      return $retval;

      
    if ($is_list) {
      if (is_null($ndx))
        if ($is_multi)
          print "return object\n";
        else
          print "return scalar\n";
      else
        if ($is_multi)
          print "return array of objects\n";
        else
          print "return array of scalars\n";
    }
    else {
      if ($is_multi)
        print "return object\n";
      else
        print "return scalar\n";
    } // not $is_list



    // unlikely?
    if ($fielditem && (is_string($fielditem) || is_numeric($fielditem)))
      return $fielditem;
    
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
 
 //var_dump($subfield);
 
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
    return $retval;  
  } // get()


} // NnodeClass

