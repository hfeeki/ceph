#include "rgw_op.h"
#include "rgw_user.h"
#include "rgw_rest_user.h"

#include "include/str_list.h"

#define dout_subsys ceph_subsys_rgw

class RGWOp_User_Info : public RGWRESTOp {

public:
  RGWOp_User_Info() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_READ);
  }

  void execute();

  virtual const char *name() { return "get_user_info"; }
};

void RGWOp_User_Info::execute()
{
  RGWUserAdminOpState op_state;

  std::string uid;

  RESTArgs::get_string(s, "uid", uid, &uid);

  // FIXME: no double checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  http_ret = RGWUserAdminOp_User::info(store, op_state, flusher);
}

class RGWOp_User_Create : public RGWRESTOp {

public:
  RGWOp_User_Create() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "create_user"; }
};

void RGWOp_User_Create::execute()
{
  std::string uid;
  std::string display_name;
  std::string email;
  std::string access_key;
  std::string secret_key;
  std::string caps;

  bool gen_key; // FIXME: need to add to RGWAdminOpState
  bool suspended;

  uint32_t max_buckets;
  int32_t key_type;

  RGWUserAdminOpState op_state;

  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_string(s, "display-name", display_name, &display_name);
  RESTArgs::get_string(s, "email", email, &email);
  RESTArgs::get_string(s, "access-key", access_key, &access_key);
  RESTArgs::get_string(s, "secret-key", secret_key, &secret_key);
  RESTArgs::get_string(s, "caps", caps, &caps);
  RESTArgs::get_bool(s, "gen-key", true, &gen_key);
  RESTArgs::get_bool(s, "suspended", false, &suspended);
  RESTArgs::get_uint32(s, "max-buckets", RGW_DEFAULT_MAX_BUCKETS, &max_buckets);
  RESTArgs::get_int32(s, "key-type", KEY_TYPE_S3, &key_type);

  // FIXME: don't do double argument checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (!display_name.empty())
    op_state.set_display_name(display_name);

  if (!email.empty())
    op_state.set_user_email(email);

  if (!caps.empty())
    op_state.set_caps(caps);

  if (!access_key.empty())
    op_state.set_access_key(access_key);

  if (!secret_key.empty())
    op_state.set_secret_key(secret_key);

  if (key_type > -1)
    op_state.set_key_type(key_type);

  if (max_buckets != RGW_DEFAULT_MAX_BUCKETS)
    op_state.set_max_buckets(max_buckets);

  if (!gen_key)
    //op_state.set_gen_key(gen_key)  // FIXME

  if (suspended)
    op_state.set_suspension(true);

  http_ret = RGWUserAdminOp_User::create(store, op_state, flusher); 
}

class RGWOp_User_Modify : public RGWRESTOp {

public:
  RGWOp_User_Modify() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "modify_user"; }
};

void RGWOp_User_Modify::execute()
{
  std::string uid;
  std::string display_name;
  std::string email;
  std::string access_key;
  std::string secret_key;
  std::string caps;

  bool gen_key; // FIXME: need to add to RGWAdminOpState
  bool suspended;

  uint32_t max_buckets;
  int32_t key_type;

  RGWUserAdminOpState op_state;

  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_string(s, "display-name", display_name, &display_name);
  RESTArgs::get_string(s, "email", email, &email);
  RESTArgs::get_string(s, "access-key", access_key, &access_key);
  RESTArgs::get_string(s, "secret-key", secret_key, &secret_key);
  RESTArgs::get_string(s, "caps", caps, &caps);
  RESTArgs::get_bool(s, "generate-key", true, &gen_key);
  RESTArgs::get_bool(s, "suspended", false, &suspended);
  RESTArgs::get_uint32(s, "max-buckets", RGW_DEFAULT_MAX_BUCKETS, &max_buckets);
  RESTArgs::get_int32(s, "key-type", KEY_TYPE_S3, &key_type);

  // FIXME: don't do double argument checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (!display_name.empty())
    op_state.set_display_name(display_name);

  if (!email.empty())
    op_state.set_user_email(email);

  if (!caps.empty())
    op_state.set_caps(caps);

  if (!access_key.empty())
    op_state.set_access_key(access_key);

  if (!secret_key.empty())
    op_state.set_secret_key(secret_key);

  if (key_type > -1)
    op_state.set_key_type(key_type);

  if (max_buckets != RGW_DEFAULT_MAX_BUCKETS)
    op_state.set_max_buckets(max_buckets);

  if (!gen_key)
    //op_state.set_gen_key(gen_key)  // FIXME

  if (suspended)
    op_state.set_suspension(true);

  http_ret = RGWUserAdminOp_User::modify(store, op_state, flusher); 
}

class RGWOp_User_Remove : public RGWRESTOp {

public:
  RGWOp_User_Remove() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "remove_user"; }
};

void RGWOp_User_Remove::execute()
{
  std::string uid;
  bool purge_data;

  RGWUserAdminOpState op_state;

  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_bool(s, "purge-data", false, &purge_data);

  // FIXME: no double checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (purge_data)
    op_state.set_purge_data();

  http_ret = RGWUserAdminOp_User::remove(store, op_state, flusher);
}

class RGWOp_Subuser_Create : public RGWRESTOp {

public:
  RGWOp_Subuser_Create() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "create_subuser"; }
};

void RGWOp_Subuser_Create::execute()
{
  std::string uid;
  std::string subuser;
  std::string secret_key;

  bool gen_subuser; // FIXME: has no effect
  uint32_t perm_mask;
  int32_t key_type;

  RGWUserAdminOpState op_state;

  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_string(s, "subuser", subuser, &subuser);
  RESTArgs::get_string(s, "secret-key", secret_key, &secret_key);
  RESTArgs::get_bool(s, "generate-subuser", false, &gen_subuser);
  RESTArgs::get_uint32(s, "access", 0, &perm_mask);
  RESTArgs::get_int32(s, "key-type", KEY_TYPE_SWIFT, &key_type);

  // FIXME: no double checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (!subuser.empty())
    op_state.set_subuser(subuser);

  if (!secret_key.empty())
    op_state.set_secret_key(secret_key);

  if (perm_mask != 0)
    op_state.set_perm(perm_mask);

  if (gen_subuser)
    // op_state.set_gen_subuser(); // FIXME

  op_state.set_key_type(key_type);

  http_ret = RGWUserAdminOp_Subuser::create(store, op_state, flusher);
}

class RGWOp_Subuser_Modify : public RGWRESTOp {

public:
  RGWOp_Subuser_Modify() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "modify_subuser"; }
};

void RGWOp_Subuser_Modify::execute()
{
  std::string uid;
  std::string subuser;
  std::string secret_key;

  RGWUserAdminOpState op_state;

  uint32_t perm_mask;
  int32_t key_type;

  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_string(s, "subuser", subuser, &subuser);
  RESTArgs::get_string(s, "secret-key", secret_key, &secret_key);
  RESTArgs::get_uint32(s, "access", 0, &perm_mask);
  RESTArgs::get_int32(s, "key-type", KEY_TYPE_SWIFT, &key_type);

  // FIXME: no double checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (!subuser.empty())
    op_state.set_subuser(subuser);

  if (!secret_key.empty())
    op_state.set_secret_key(secret_key);

  if (perm_mask != 0)
    op_state.set_perm(perm_mask);

  op_state.set_key_type(key_type);

  http_ret = RGWUserAdminOp_Subuser::modify(store, op_state, flusher);
}

class RGWOp_Subuser_Remove : public RGWRESTOp {

public:
  RGWOp_Subuser_Remove() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "remove_subuser"; }
};

void RGWOp_Subuser_Remove::execute()
{
  std::string uid;
  std::string subuser;
  bool purge_keys;

  RGWUserAdminOpState op_state;
  
  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_string(s, "subuser", subuser, &subuser);
  RESTArgs::get_bool(s, "purge-keys", true, &purge_keys);

  // FIXME: no double checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (!subuser.empty())
    op_state.set_subuser(subuser);

  if (purge_keys)
    op_state.set_purge_keys();

  http_ret = RGWUserAdminOp_Subuser::remove(store, op_state, flusher);
}

class RGWOp_Key_Create : public RGWRESTOp {

public:
  RGWOp_Key_Create() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "create_access_key"; }
};

void RGWOp_Key_Create::execute()
{
  std::string uid;
  std::string subuser;
  std::string access_key;
  std::string secret_key;

  int32_t key_type;
  bool gen_key;

  RGWUserAdminOpState op_state;
  
  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_string(s, "subuser", subuser, &subuser);
  RESTArgs::get_string(s, "access-key", access_key, &access_key);
  RESTArgs::get_string(s, "secret-key", secret_key, &secret_key);
  RESTArgs::get_int32(s, "key-type", KEY_TYPE_S3, &key_type);
  RESTArgs::get_bool(s, "generate-key", false, &gen_key);
  
  // FIXME: no double checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (!subuser.empty())
    op_state.set_subuser(subuser);

  if (!access_key.empty())
    op_state.set_access_key(access_key);

  if (!secret_key.empty())
    op_state.set_secret_key(secret_key);

  if (gen_key)
    // op_state.set_gen_key(); FIXME

  op_state.set_key_type(key_type);

  http_ret = RGWUserAdminOp_Key::create(store, op_state, flusher);
}

class RGWOp_Key_Remove : public RGWRESTOp {

public:
  RGWOp_Key_Remove() {}

  int check_caps(RGWUserCaps& caps) {
    return caps.check_cap("users", RGW_CAP_WRITE);
  }

  void execute();

  virtual const char *name() { return "remove_access_key"; }
};

void RGWOp_Key_Remove::execute()
{
  std::string uid;
  std::string subuser;
  std::string access_key;

  int32_t key_type;

  RGWUserAdminOpState op_state;
  
  RESTArgs::get_string(s, "uid", uid, &uid);
  RESTArgs::get_string(s, "subuser", subuser, &subuser);
  RESTArgs::get_int32(s, "key-type", -1, &key_type);
  
  // FIXME: no double checking
  if (!uid.empty())
    op_state.set_user_id(uid);

  if (!subuser.empty())
    op_state.set_subuser(subuser);

  if (!access_key.empty())
    op_state.set_access_key(access_key);

  http_ret = RGWUserAdminOp_Key::remove(store, op_state, flusher);
}

RGWOp *RGWHandler_User::op_get()
{
  return new RGWOp_User_Info;
};

RGWOp *RGWHandler_User::op_put()
{
  if (s->args.sub_resource_exists("subusers"))
    return new RGWOp_Subuser_Create;

  if (s->args.sub_resource_exists("keys"))
    return new RGWOp_Key_Create;

  return new RGWOp_User_Create;
};

RGWOp *RGWHandler_User::op_post()
{
  if (s->args.sub_resource_exists("subusers"))
    return new RGWOp_Subuser_Modify;

  return new RGWOp_User_Modify;
};

RGWOp *RGWHandler_User::op_delete()
{
   if (s->args.sub_resource_exists("subusers"))
    return new RGWOp_Subuser_Remove;

  if (s->args.sub_resource_exists("keys"))
    return new RGWOp_Key_Remove;

  return new RGWOp_User_Remove;
};

