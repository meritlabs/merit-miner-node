{
  "targets": [
    {
      "target_name": "meritminer",
      "sources": [ "native/meritminer.cpp" ],
        'link_settings': {
            'libraries': [
                '/usr/local/lib/libfatmeritminer.a'
            ]
        },
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ]
    }
  ]
}


