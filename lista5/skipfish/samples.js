var mime_samples = [
  { 'mime': 'application/xhtml+xml', 'samples': [
    { 'url': 'http://127.0.0.1:8000/', 'dir': '_m0/0', 'linked': 2, 'len': 302 },
    { 'url': 'http://127.0.0.1:8000/dane_przelewu', 'dir': '_m0/1', 'linked': 2, 'len': 809 },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'dir': '_m0/2', 'linked': 5, 'len': 1663 },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'dir': '_m0/3', 'linked': 5, 'len': 1860 },
    { 'url': 'http://127.0.0.1:8000/przelewy', 'dir': '_m0/4', 'linked': 2, 'len': 426 } ]
  },
  { 'mime': 'text/html', 'samples': [
    { 'url': 'http://127.0.0.1:8000/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000001v293924\x3e', 'dir': '_m1/0', 'linked': 2, 'len': 148 },
    { 'url': 'http://127.0.0.1:8000/admin/auth/group/', 'dir': '_m1/1', 'linked': 0, 'len': 26 },
    { 'url': 'http://127.0.0.1:8000/admin/logout/./', 'dir': '_m1/2', 'linked': 0, 'len': 89 } ]
  }
];

var issue_samples = [
  { 'severity': 3, 'type': 40701, 'samples': [
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'extra': '', 'sid': '0', 'dir': '_i0/0' },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'extra': '', 'sid': '0', 'dir': '_i0/1' },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'extra': '', 'sid': '0', 'dir': '_i0/2' },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'extra': '', 'sid': '0', 'dir': '_i0/3' } ]
  },
  { 'severity': 3, 'type': 40601, 'samples': [
    { 'url': 'http://127.0.0.1:8000/', 'extra': 'implicitly cacheable \x27Set-Cookie\x27 response', 'sid': '0', 'dir': '_i1/0' },
    { 'url': 'http://127.0.0.1:8000/dane_przelewu', 'extra': 'implicitly cacheable \x27Set-Cookie\x27 response', 'sid': '0', 'dir': '_i1/1' } ]
  },
  { 'severity': 3, 'type': 40304, 'samples': [
    { 'url': 'http://127.0.0.1:8000/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000001v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/0' },
    { 'url': 'http://127.0.0.1:8000/admin/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000048v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/1' },
    { 'url': 'http://127.0.0.1:8000/admin/auth/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000066v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/2' },
    { 'url': 'http://127.0.0.1:8000/admin/login/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000090v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/3' },
    { 'url': 'http://127.0.0.1:8000/admin/logout/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000054v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/4' },
    { 'url': 'http://127.0.0.1:8000/static/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000084v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/5' },
    { 'url': 'http://127.0.0.1:8000/static/admin/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000102v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/6' },
    { 'url': 'http://127.0.0.1:8000/static/admin/css/.htaccess.aspx--\x3e\x22\x3e\x27\x3e\x27\x22\x3csfi000114v293924\x3e', 'extra': '', 'sid': '0', 'dir': '_i2/7' } ]
  },
  { 'severity': 2, 'type': 30601, 'samples': [
    { 'url': 'http://127.0.0.1:8000/wyslij_dane/', 'extra': '', 'sid': '0', 'dir': '_i3/0' } ]
  },
  { 'severity': 0, 'type': 10803, 'samples': [
    { 'url': 'http://127.0.0.1:8000/sfi9876', 'extra': '', 'sid': '0', 'dir': '_i4/0' },
    { 'url': 'http://127.0.0.1:8000/admin/./', 'extra': '', 'sid': '0', 'dir': '_i4/1' },
    { 'url': 'http://127.0.0.1:8000/admin/auth/./', 'extra': '', 'sid': '0', 'dir': '_i4/2' },
    { 'url': 'http://127.0.0.1:8000/admin/auth/group/', 'extra': '', 'sid': '0', 'dir': '_i4/3' },
    { 'url': 'http://127.0.0.1:8000/admin/login/./', 'extra': '', 'sid': '0', 'dir': '_i4/4' },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'extra': '', 'sid': '0', 'dir': '_i4/5' },
    { 'url': 'http://127.0.0.1:8000/admin/login/?next=/admin/', 'extra': '', 'sid': '0', 'dir': '_i4/6' },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'extra': '', 'sid': '0', 'dir': '_i4/7' },
    { 'url': 'http://127.0.0.1:8000/admin/login/', 'extra': '', 'sid': '0', 'dir': '_i4/8' },
    { 'url': 'http://127.0.0.1:8000/admin/logout/./', 'extra': '', 'sid': '0', 'dir': '_i4/9' },
    { 'url': 'http://127.0.0.1:8000/static/', 'extra': '', 'sid': '0', 'dir': '_i4/10' },
    { 'url': 'http://127.0.0.1:8000/static/admin/', 'extra': '', 'sid': '0', 'dir': '_i4/11' },
    { 'url': 'http://127.0.0.1:8000/static/admin/css/', 'extra': '', 'sid': '0', 'dir': '_i4/12' },
    { 'url': 'http://127.0.0.1:8000/zaloguj', 'extra': '', 'sid': '0', 'dir': '_i4/13' },
    { 'url': 'http://127.0.0.1:8000/zaloguj?next=/wyslij_dane/', 'extra': '', 'sid': '0', 'dir': '_i4/14' },
    { 'url': 'http://127.0.0.1:8000/dane_przelewu', 'extra': '', 'sid': '0', 'dir': '_i4/15' },
    { 'url': 'http://127.0.0.1:8000/przelewy', 'extra': '', 'sid': '0', 'dir': '_i4/16' },
    { 'url': 'http://127.0.0.1:8000/wyslij_dane', 'extra': '', 'sid': '0', 'dir': '_i4/17' },
    { 'url': 'http://127.0.0.1:8000/wyslij_dane/', 'extra': '', 'sid': '0', 'dir': '_i4/18' },
    { 'url': 'http://127.0.0.1:8000/wyslij_dane/', 'extra': '', 'sid': '0', 'dir': '_i4/19' },
    { 'url': 'http://127.0.0.1:8000/wyslij_dane/', 'extra': '', 'sid': '0', 'dir': '_i4/20' },
    { 'url': 'http://127.0.0.1:8000/wyslij_dane/', 'extra': '', 'sid': '0', 'dir': '_i4/21' } ]
  },
  { 'severity': 0, 'type': 10505, 'samples': [
    { 'url': 'http://127.0.0.1:8000/dane_przelewu', 'extra': 'amount', 'sid': '0', 'dir': '_i5/0' },
    { 'url': 'http://127.0.0.1:8000/dane_przelewu', 'extra': 'target', 'sid': '0', 'dir': '_i5/1' } ]
  },
  { 'severity': 0, 'type': 10405, 'samples': [
    { 'url': 'http://127.0.0.1:8000/admin/auth/', 'extra': '', 'sid': '0', 'dir': '_i6/0' },
    { 'url': 'http://127.0.0.1:8000/admin/auth/group/', 'extra': '', 'sid': '0', 'dir': '_i6/1' },
    { 'url': 'http://127.0.0.1:8000/admin/logout/', 'extra': '', 'sid': '0', 'dir': '_i6/2' } ]
  },
  { 'severity': 0, 'type': 10205, 'samples': [
    { 'url': 'http://127.0.0.1:8000/sfi9876', 'extra': '', 'sid': '0', 'dir': '_i7/0' },
    { 'url': 'http://127.0.0.1:8000/admin/auth/group/sfi9876/', 'extra': '', 'sid': '0', 'dir': '_i7/1' },
    { 'url': 'http://127.0.0.1:8000/admin/auth/group/sfi9876', 'extra': '', 'sid': '0', 'dir': '_i7/2' } ]
  },
  { 'severity': 0, 'type': 10204, 'samples': [
    { 'url': 'http://127.0.0.1:8000/', 'extra': 'X-Frame-Options', 'sid': '0', 'dir': '_i8/0' } ]
  },
  { 'severity': 0, 'type': 10202, 'samples': [
    { 'url': 'http://127.0.0.1:8000/', 'extra': 'WSGIServer/0.2 CPython/3.6.3', 'sid': '0', 'dir': '_i9/0' } ]
  },
  { 'severity': 0, 'type': 10201, 'samples': [
    { 'url': 'http://127.0.0.1:8000/', 'extra': 'sessionid', 'sid': '0', 'dir': '_i10/0' },
    { 'url': 'http://127.0.0.1:8000/dane_przelewu/', 'extra': 'csrftoken', 'sid': '0', 'dir': '_i10/1' } ]
  }
];

