<?php
/*
 * This is generated code!!!!
 * DO NOT EDIT!!! (unless you want to fork this on it's own)
 * Use "drush @slndev scr test/drush/drupalFields2class1.drush sln_project_360" 
 * on command line from within the dlib root folder
 */

error_reporting(E_ALL);

// TODO: make this relative
drush_include("/home/markus/projects/dlib/src", "node.class");


class sln_project_360Class extends nodeClass {

  // remove?
  protected $project = NULL; // why? we already have $node;

  public function __construct($node) {
    parent::__construct($node);
    $this->project = $node; // uncessary
  }

  // override
  public function toString() { return var_export($this->project, 1); }

  // properties
  public title = $this->get('title')
  public path = $this->get('path')
  public field_project_manager = $this->get('field_project_manager')
  public field_project_subject = $this->get('field_project_subject')
  public field_project_supervisor = $this->get('field_project_supervisor')
  public field_project_observers = $this->get('field_project_observers')
  public field_messaging_subject_message = $this->get('field_messaging_subject_message')
  public field_messaging_sup_message = $this->get('field_messaging_sup_message')
  public field_messaging_obs_message = $this->get('field_messaging_obs_message')
  public field_project_messaging_topic = $this->get('field_project_messaging_topic')
  public field_project_messaging_reply_to = $this->get('field_project_messaging_reply_to')
  public field_project_messaging_from = $this->get('field_project_messaging_from')
  public field_project_form_self = $this->get('field_project_form_self')
  public field_project_form_supervisor = $this->get('field_project_form_supervisor')
  public field_project_form_observer = $this->get('field_project_form_observer')
  public field_project_form_planning = $this->get('field_project_form_planning')
  public field_project_group = $this->get('field_project_group')
  public field_project_status = $this->get('field_project_status')
  public field_project_is_complete = $this->get('field_project_is_complete')
  public field_project_type = $this->get('field_project_type')
  public field_project_short_code = $this->get('field_project_short_code')
  public field_project_survey_language = $this->get('field_project_survey_language')
  public field_project_logo = $this->get('field_project_logo')

  // methods
  public function get_title() { return $this->out($this->_project->title, 1); }
  public function set_title($title) {}

  public function get_path() { return $this->out($this->_project->path, 1); }
  public function set_path($path) {}

  public function get_field_project_manager() { return $this->out($this->_project->field_project_manager, 1); }
  public function set_field_project_manager($field_project_manager) {}

  public function get_field_project_subject() { return $this->out($this->_project->field_project_subject, 1); }
  public function set_field_project_subject($field_project_subject) {}

  public function get_field_project_supervisor() { return $this->out($this->_project->field_project_supervisor, 1); }
  public function set_field_project_supervisor($field_project_supervisor) {}

  public function get_field_project_observers() { return $this->out($this->_project->field_project_observers, 1); }
  public function set_field_project_observers($field_project_observers) {}

  public function get_field_messaging_subject_message() { return $this->out($this->_project->field_messaging_subject_message, 1); }
  public function set_field_messaging_subject_message($field_messaging_subject_message) {}

  public function get_field_messaging_sup_message() { return $this->out($this->_project->field_messaging_sup_message, 1); }
  public function set_field_messaging_sup_message($field_messaging_sup_message) {}

  public function get_field_messaging_obs_message() { return $this->out($this->_project->field_messaging_obs_message, 1); }
  public function set_field_messaging_obs_message($field_messaging_obs_message) {}

  public function get_field_project_messaging_topic() { return $this->out($this->_project->field_project_messaging_topic, 1); }
  public function set_field_project_messaging_topic($field_project_messaging_topic) {}

  public function get_field_project_messaging_reply_to() { return $this->out($this->_project->field_project_messaging_reply_to, 1); }
  public function set_field_project_messaging_reply_to($field_project_messaging_reply_to) {}

  public function get_field_project_messaging_from() { return $this->out($this->_project->field_project_messaging_from, 1); }
  public function set_field_project_messaging_from($field_project_messaging_from) {}

  public function get_field_project_form_self() { return $this->out($this->_project->field_project_form_self, 1); }
  public function set_field_project_form_self($field_project_form_self) {}

  public function get_field_project_form_supervisor() { return $this->out($this->_project->field_project_form_supervisor, 1); }
  public function set_field_project_form_supervisor($field_project_form_supervisor) {}

  public function get_field_project_form_observer() { return $this->out($this->_project->field_project_form_observer, 1); }
  public function set_field_project_form_observer($field_project_form_observer) {}

  public function get_field_project_form_planning() { return $this->out($this->_project->field_project_form_planning, 1); }
  public function set_field_project_form_planning($field_project_form_planning) {}

  public function get_field_project_group() { return $this->out($this->_project->field_project_group, 1); }
  public function set_field_project_group($field_project_group) {}

  public function get_field_project_status() { return $this->out($this->_project->field_project_status, 1); }
  public function set_field_project_status($field_project_status) {}

  public function get_field_project_is_complete() { return $this->out($this->_project->field_project_is_complete, 1); }
  public function set_field_project_is_complete($field_project_is_complete) {}

  public function get_field_project_type() { return $this->out($this->_project->field_project_type, 1); }
  public function set_field_project_type($field_project_type) {}

  public function get_field_project_short_code() { return $this->out($this->_project->field_project_short_code, 1); }
  public function set_field_project_short_code($field_project_short_code) {}

  public function get_field_project_survey_language() { return $this->out($this->_project->field_project_survey_language, 1); }
  public function set_field_project_survey_language($field_project_survey_language) {}

  public function get_field_project_logo() { return $this->out($this->_project->field_project_logo, 1); }
  public function set_field_project_logo($field_project_logo) {}


} // sln_project_360Class


class sln_project_360ClassFactory {
  public static function create($node) {
    return new sln_project_360Class($node);
  }
} // sln_project_360ClassFactory


// example usage

$id = 305;  // random nid, adjust for your own testing

$o = sln_project_360ClassFactory:create($id);

print $o->title;

var_dump($o);


