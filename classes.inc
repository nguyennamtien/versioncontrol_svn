<?php

class VersioncontrolSvnRepository extends VersioncontrolRepository {
  public $vcs = 'svn';

  public $update_method;
  public $updated;
  public $last_revision;
  public $auth_username;
  public $auth_password;
  public $path_trunk;
  public $path_branches;
  public $path_tags;
  public $is_working_copy;

  protected function buildQuery() {
    $query = parent::buildQuery();
    $query->join('versioncontrol_svn_repositories', 'vsr', 'vr.repo_id = vsr.repo_id AND vr.repo_id = :id', array(':id' => $this->repo_id));
    $query->fields('vsr', drupal_schema_fields_sql('versioncontrol_svn_repositories'));
    return $query;
  }

  public function build($args = array()) {
    $serialized = array('data', 'auth_username', 'auth_password', 'path_trunk', 'path_branches', 'path_tags');
    foreach ($args as $prop => $value) {
      $this->$prop = in_array($prop, $serialized) ? unserialize($value) : $value;
    }
  }
}