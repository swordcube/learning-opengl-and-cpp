import shutil
import SCons

def GlobRecursive(pattern, node='.'):
    results = []
    for f in Glob(str(node) + '/*', source=True):
        if type(f) is SCons.Node.FS.Dir:
            results += GlobRecursive(pattern, f)
    results += Glob(str(node) + '/' + pattern, source=True)
    return results

env = Environment(
    CPPPATH=['include'],
    CPPFLAGS='-O2',
    LIBS = ['SDL2', 'GL']
)
env.Program(target='export/Testicle', source=GlobRecursive("*.c*", "src/"))
shutil.copytree(src = 'assets', dst = 'export/assets', dirs_exist_ok = True)