{
  "targets": [
    {
      "target_name": "meritminer",
      "sources": [ "native/meritminer.cpp" ],
        'link_settings': {
            'libraries': [
                '-lmeritminer',
                '-lcryptopp',
                '-lboost_log',
                '-lboost_system',
                '-lboost_program_options',
                '-lboost_filesystem',
                '-lboost_regex',
                '-lboost_thread'
            ]
        },
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ]
      
    }
  ]
}


