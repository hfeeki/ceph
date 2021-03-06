// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
#ifndef CEPH_INODE_BACKTRACE_H
#define CEPH_INODE_BACKTRACE_H

#include "mdstypes.h"

namespace ceph {
  class Formatter;
}

/** metadata backpointers **/

/*
 * - inode_backpointer_t is just the _pointer_ portion; it doesn't
 *   tell us who we point _from_.
 *
 * - it _does_ include a version of the source object, so we can look
 *   at two different pointers (from the same inode) and tell which is
 *   newer.
 */
struct inode_backpointer_t {
  inodeno_t dirino;    // containing directory ino
  string dname;        // linking dentry name
  version_t version;   // child's version at time of backpointer creation

  inode_backpointer_t() : version(0) {}
  inode_backpointer_t(inodeno_t i, const string &d, version_t v) : dirino(i), dname(d), version(v) {}

  void encode(bufferlist& bl) const;
  void decode(bufferlist::iterator &bl);
  void decode_old(bufferlist::iterator &bl);
  void dump(Formatter *f) const;
  static void generate_test_instances(list<inode_backpointer_t*>& ls);
};
WRITE_CLASS_ENCODER(inode_backpointer_t)

inline ostream& operator<<(ostream& out, const inode_backpointer_t& ib) {
  return out << "<" << ib.dirino << "/" << ib.dname << " v" << ib.version << ">";
}

/*
 * inode_backtrace_t is a complete ancestor backtraces for a given inode.
 * we include who _we_ are, so that the backtrace can stand alone (as, say,
 * an xattr on an object).
 */
struct inode_backtrace_t {
  inodeno_t ino;       // my ino
  vector<inode_backpointer_t> ancestors;
  int64_t pool;
  // we use a set for old_pools to avoid duplicate entries, e.g. setlayout 0, 1, 0
  set<int64_t> old_pools;

  inode_backtrace_t() : pool(-1) {}

  void encode(bufferlist& bl) const;
  void decode(bufferlist::iterator &bl);
  void dump(Formatter *f) const;
  static void generate_test_instances(list<inode_backtrace_t*>& ls);
};
WRITE_CLASS_ENCODER(inode_backtrace_t)

inline ostream& operator<<(ostream& out, const inode_backtrace_t& it) {
  return out << "(" << it.pool << ")" << it.ino << ":" << it.ancestors << "//" << it.old_pools;
}


#endif

