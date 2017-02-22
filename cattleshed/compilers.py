import json

def merge(*args):
    result = {}
    for dic in args:
        result.update(dic)
    return result

class Switches(object):
    def resolve_conflicts(self, pairs):
        conflicts = [p[0] for p in pairs]
        return [(p[0], merge(p[1], { "conflicts": conflicts })) for p in pairs]

    def make_boost_header(self):
        pairs = [
            ("boost-nothing-header", {
                "flags":[],
                "display-name":"Don't Use Boost",
                "display-flags":"",
                "runtime":True,
            }),
            ("boost-1.55-header", {
                "flags":["-I/usr/local/boost-1.55.0/include"],
                "display-name":"Boost 1.55.0",
                "display-flags":"-I/usr/local/boost-1.55.0/include",
                "runtime":True,
            }),
        ]
        return self.resolve_conflicts(pairs)

    def make_default(self):
        return {
            "mono-optimize":{
                "flags":"-optimize",
                "display-name":"Optimization",
            },
            "cpp-p":{
                "flags":["-P"],
                "display-name":"-P",
                "runtime":True,
            },
        }

    def make(self):
        return merge(
            self.make_default(),
            self.make_boost_header())

class Compilers(object):
    def resolve_format(self, formats, **kwargs):
        def typedo(value):
            if isinstance(value, str):
                return value.format(**kwargs)
            elif isinstance(value, (list, dict)):
                return self.resolve_format(value, **kwargs)
            else:
                return value

        if isinstance(formats, list):
            return [typedo(value) for value in formats]
        else:
            return {key:typedo(value) for key,value in formats.iteritems()}

    def make_common(self, names, formats):
        params = {
            name[0]: self.resolve_format(formats, name=name[0], **name[1]["params"])
            for name in names
        }
        after = {
            name[0]: name[1]["after"]
            for name in names
        }
        compilers = [merge(
            { "name": name[0] },
            params[name[0]],
            after[name[0]],
        ) for name in names]

        return compilers

    def make_mono(self):
        NAMES = [
            ("mcs-2.6.7", {
                "params": {
                    "mono": "mono-2.6.7",
                },
                "after": {
                    "display-name":"gmcs for Unity on iOS",
                    "display-compile-command":"gmcs -out:prog.exe prog.cs",
                    "compile-command":["/usr/local/mono-2.6.7/bin/gmcs-custom", "-out:prog.exe", "prog.cs"],
                    "run-command":["/usr/local/mono-2.6.7/bin/mono-custom", "prog.exe"]
                },
            }),
        ]
        FORMATS = {
            "displayable":True,
            "language":"C#",
            "output-file":"prog.cs",
            "compiler-option-raw":True,
            "compile-command":["/usr/local/{mono}/bin/mcs", "-out:prog.exe", "prog.cs"],
            "version-command":["/bin/sh", "-c", "/usr/local/{mono}/bin/mcs --version | head -1 | cut -d' ' -f5"],
            "swithes":["mono-optimize"],
            "initial-checked":[],
            "display-name":"mcs",
            "display-compile-command":"mcs -out:prog.exe prog.cs",
            "run-command":["/usr/local/{mono}/bin/mono", "prog.exe"]
        }
        compilers = self.make_common(NAMES, FORMATS)
        return compilers

    def make_python(self):
        NAMES = [
           ("pypy-2.1", {
                "params": {
                    "bin": "pypy",
                },
                "after": {
                    "display-name":"pypy",
                    "display-compile-command":"pypy prog.py",
                    "version-command":["/usr/local/pypy-2.1/bin/pypy", "-c", "import sys; print(sys.version.split()[7])"],
                },
           }),
        ]
        FORMATS = {
            "displayable":True,
            "output-file":"prog.py",
            "run-command":["/usr/local/{name}/bin/{bin}", "prog.py"],
            "display-name":"python",
            "display-compile-command":"python prog.py",
            "language":"Python",
            "runtime-option-raw":True,
            "compile-command":"/bin/true",
            "version-command":["/usr/local/{name}/bin/{bin}", "-c", "import sys; print(sys.version.split()[0])"],
        }
        compilers = self.make_common(NAMES, FORMATS)
        return compilers

    def make_vim(self):
        NAMES = [
           ("vim-7.4.1714", {
                "params": {
                },
                "after": {
                    "version-command":["/bin/echo", "vim 7.4.1714"],
                },
           }),
           ("vim-7.4.729", {
                "params": {
                },
                "after": {
                    "version-command":["/bin/echo", "vim 7.4.729"],
                },
           }),
        ]
        FORMATS = {
            "displayable":True,
            "output-file":"prog.vim",
            "run-command":["/usr/local/{name}/bin/vim", "-X", "-N", "-u", "NONE", "-i", "NONE", "-V1", "-e", "--cmd", "source prog.vim | qall!"],
            "display-compile-command":"vim -X -N -u NONE -i NONE -V1 -e --cmd 'source proc.vim | qall!'",
            "language":"Vim script",
            "runtime-option-raw":True,
            "compile-command":["/bin/true"],
        }
        compilers = self.make_common(NAMES, FORMATS)
        return compilers

    def make_default1(self):
        COMPILERS = [{
            "name":"gcc-4.8.2-pp",
            "displayable":True,
            "display-name":"gcc",
            "display-compile-command":"gcc prog.cpp -E",
            "language":"CPP",
            "output-file":"prog.cpp",
            "compile-command":"/bin/true",
            "runtime-option-raw":True,
            "run-command":["/usr/local/gcc-4.8.2/bin/gcc", "-E", "prog.cpp"],
            "version-command":["/usr/local/gcc-4.8.2/bin/gcc", "-dumpversion"],
            "switches":["cpp-p", "boost-nothing-header", "boost-1.55-header"],
            "initial-checked":["cpp-p", "boost-1.55-header"],
        }]
        return COMPILERS

    def make_default2(self):
        COMPILERS = [{
            "name":"bash",
            "displayable":True,
            "output-file":"prog.sh",
            "run-command":["/bin/bash", "prog.sh"],
            "display-name":"bash",
            "display-compile-command":"bash prog.sh",
            "language":"Bash script",
            "runtime-option-raw":True,
            "compile-command":"/bin/true",
            "version-command":["/bin/sh", "-c", "/bin/bash --version | head -1"],
        }]
        return COMPILERS

    def make(self):
        return (
            self.make_default1() +
            self.make_mono() +
            self.make_python() +
            self.make_vim() +
            self.make_default2()
        )

def make_config():
    return {
        "switches": Switches().make(),
        "compilers": Compilers().make(),
    }

if __name__ == '__main__':
    print json.dumps(make_config(), indent=4)
