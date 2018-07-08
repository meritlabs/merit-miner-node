{
  "targets": [
    {
      "target_name": "meritminer",
      "sources": [ "native/meritminer.cpp" ],
      "conditions" : [
              ['OS=="mac"', {
                'link_settings': {
                    'libraries': [
                        '/usr/local/lib/libfatmeritminer.a'
                    ]
                },
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ]
              }],
              ['OS=="linux"', {
                'link_settings': {
                    'libraries': [
                        '/usr/local/lib/libfatmeritminer.a'
                    ]
                },
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ]
              }],
              ['OS=="win"', {
                'link_settings': {
                    'libraries': [
                        "C:/libmeritminer/build/libfatmeritminer.lib",
                        "C:/Boost/lib/libboost_date_time-vc141-mt-s-x64-1_67.lib",
                        "C:/Boost/lib/libboost_regex-vc141-mt-s-x64-1_67.lib",
                        "C:/Boost/lib/libboost_system-vc141-mt-s-x64-1_67.lib"
                    ]
                },
                'include_dirs': [
                        "C:/libmeritminer/include"
                ],
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ]
              }]
      ]
    }
  ]
}
