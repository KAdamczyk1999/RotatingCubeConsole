src = []
src += '../main.cpp'
src += 'AlgebraTest.cpp'

src += '../../src/lin_alg.c'

inc = []
inc += include_directories('../../inc')

dep = []
dep += dependency('gtest')
dep += dependency('gmock')

app = executable('AlgebraTest', src, include_directories : inc, dependencies : dep)

test('AlgebraTest', app)