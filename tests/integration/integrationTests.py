import subprocess

def test1():
    res=subprocess.run(["build/app.exe", "--float"], input="125*2314/4",text=True,capture_output=True)
    assert res.returncode == 0
    assert float(res.stdout) == 72312.5000

def test2():
    res=subprocess.run(["build/app.exe"], input="125*2314/4",text=True,capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 72312


def test3():
    res=subprocess.run(["build/app.exe", "--float"], input="  (  3 + 4 )  * 2", text=True,capture_output=True)
    assert res.returncode == 0
    assert float(res.stdout) == 14.0000


def test4():
    res=subprocess.run(["build/app.exe"], input="\t9\n-\n5",text=True,capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 4
