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

  protected function buildSelf() {
    $data = db_fetch_array(db_query("
      SELECT
      vr.name, vr.root, vr.authorization_method, vr.url_backend, vr.data,
      vsr.update_method, vsr.updated, vsr.last_revision, vsr.auth_username,
      vsr.auth_password, vsr.path_trunk, vsr.path_branches, vsr.path_tags,
      vsr.is_working_copy
      FROM {versioncontrol_repositories} vr
      INNER JOIN {versioncontrol_svn_repositories} vsr ON vr.repo_id = vsr.repo_id
      WHERE vr.repo_id = %d",
      $this->repo_id));

    $serialized = array('data', 'auth_username', 'auth_password', 'path_trunk', 'path_branches', 'path_tags');
    foreach ($data as $key => $value) {
      $this->$key = in_array($key, $serialized) ? unserialize($value) : $value;
    }
  }

  public function build($args = array()) {
    $serialized = array('data', 'auth_username', 'auth_password', 'path_trunk', 'path_branches', 'path_tags');
    foreach ($args as $prop => $value) {
      $this->$prop = in_array($prop, $serialized) ? unserialize($value) : $value;
    }
  }
}