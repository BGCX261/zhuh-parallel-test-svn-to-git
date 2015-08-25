from distutils.core import setup, Extension

module1 = Extension('entropical._libentropical',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/include/python2.7'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['src/ANN.cpp',
                               'src/bd_fix_rad_search.cpp',
                               'src/bd_pr_search.cpp',
                               'src/bd_search.cpp',
                               'src/bd_tree.cpp',
                               'src/brute.cpp',
                               'src/entropical.cpp',
                               'src/functions.cpp',
                               'src/kd_dump.cpp',
                               'src/kd_fix_rad_search.cpp',
                               'src/kd_pr_search.cpp',
                               'src/kd_search.cpp',
                               'src/kd_split.cpp',
                               'src/kd_tree.cpp',
                               'src/kd_util.cpp',
                               'src/perf.cpp',
                               'src/libentropical_wrap.cxx']
                               )

setup (name = 'entropical',
       version = '0.0.1',
       description = 'This is a demo package',
       author = 'Zhu H.',
       packages = ["entropical"],
       scripts = ["Entro_Analysis.py","pRDF_test.py"],
       ext_modules = [module1])
