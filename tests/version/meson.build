#############################
#
#       BUILD TEST
#
#############################

TEST_VERSION_SRC = ['./test_version.c']
test_version_1 = executable('test_version',
                files(TEST_VERSION_SRC),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test('test version 1', test_version_1, verbose: false, suite: ['version'])
