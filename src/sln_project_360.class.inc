<?php

class sln_project_360Class { 

  protected $_project = NULL;

  public function __construct($node) { $this->_project = $node; }
  public function toString() { return var_export($this->_project, 1); }
  protected function out($obj) { return is_string($obj) ? $obj : var_export($obj, 1); }

  public function get_title() { return $this->out($this->_project->title, 1); }
  public function set_title($title) {}

  public function get_path() { return $this->out($this->_project->path, 1); }
  public function set_path($path) {}

  public function get_manager() { return $this->out($this->_project->field_project_manager, 1); }
  public function set_manager($manager) {}

  public function get_subject() { return $this->out($this->_project->field_project_subject, 1); }
  public function set_subject($subject) {}

  public function get_supervisor() { return $this->out($this->_project->field_project_supervisor, 1); }
  public function set_supervisor($supervisor) {}

  public function get_observers() { return $this->out($this->_project->field_project_observers, 1); }
  public function set_observers($observers) {}

  public function get_messaging_subject_message() { return $this->out($this->_project->field_messaging_subject_message, 1); }
  public function set_messaging_subject_message($messaging_subject_message) {}

  public function get_messaging_sup_message() { return $this->out($this->_project->field_messaging_sup_message, 1); }
  public function set_messaging_sup_message($messaging_sup_message) {}

  public function get_messaging_obs_message() { return $this->out($this->_project->field_messaging_obs_message, 1); }
  public function set_messaging_obs_message($messaging_obs_message) {}

  public function get_messaging_topic() { return $this->out($this->_project->field_project_messaging_topic, 1); }
  public function set_messaging_topic($messaging_topic) {}

  public function get_messaging_reply_to() { return $this->out($this->_project->field_project_messaging_reply_to, 1); }
  public function set_messaging_reply_to($messaging_reply_to) {}

  public function get_messaging_from() { return $this->out($this->_project->field_project_messaging_from, 1); }
  public function set_messaging_from($messaging_from) {}

  public function get_form_self() { return $this->out($this->_project->field_project_form_self, 1); }
  public function set_form_self($form_self) {}

  public function get_form_supervisor() { return $this->out($this->_project->field_project_form_supervisor, 1); }
  public function set_form_supervisor($form_supervisor) {}

  public function get_form_observer() { return $this->out($this->_project->field_project_form_observer, 1); }
  public function set_form_observer($form_observer) {}

  public function get_form_planning() { return $this->out($this->_project->field_project_form_planning, 1); }
  public function set_form_planning($form_planning) {}

  public function get_group() { return $this->out($this->_project->field_project_group, 1); }
  public function set_group($group) {}

  public function get_status() { return $this->out($this->_project->field_project_status, 1); }
  public function set_status($status) {}

  public function get_is_complete() { return $this->out($this->_project->field_project_is_complete, 1); }
  public function set_is_complete($is_complete) {}

  public function get_type() { return $this->out($this->_project->field_project_type, 1); }
  public function set_type($type) {}

  public function get_short_code() { return $this->out($this->_project->field_project_short_code, 1); }
  public function set_short_code($short_code) {}

  public function get_survey_language() { return $this->out($this->_project->field_project_survey_language, 1); }
  public function set_survey_language($survey_language) {}

  public function get_logo() { return $this->out($this->_project->field_project_logo, 1); }
  public function set_logo($logo) {}


} // sln_project_360Class

