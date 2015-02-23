# Configuration file for VIMs plugin YouCompleteMe
#
# Just ignore this file if you don't use that tool.
def FlagsForFile( filename, **kwargs ):
    return {
        "flags": ["-std=c++11"],
        "do_cache": True
    }
