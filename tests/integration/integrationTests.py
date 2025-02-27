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
    res=subprocess.run(["build/app.exe"], input="5+(11*8)/4",text=True,capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 27

def test4():
    res=subprocess.run(["build/app.exe", "--float"], input="(125*2314-(231-(123*8)+(((16*8)-97)/12)))/3",text=True,capture_output=True)
    assert res.returncode == 0
    assert float(res.stdout) == 96666.8056


def test5():
    res=subprocess.run(["build/app.exe", "--float"], input="(125*2314-(231-(123*8)+(((16*8)-97)/12)*(2+1)))/3",text=True,capture_output=True)
    assert res.returncode == 0
    assert float(res.stdout) == 96665.0833

def test6():
    res=subprocess.run(["build/app.exe", "--float"], input="  (  3 + 4 )  * 2", text=True,capture_output=True)
    assert res.returncode == 0
    assert float(res.stdout) == 14.0000


def test7():
    res=subprocess.run(["build/app.exe"], input="\t9\n-\n5",text=True,capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 4

def test8():
    res=subprocess.run(["build/app.exe"], input="((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2+1+(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((2*4)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))",text=True,capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 11

def test9():
    res=subprocess.run(["build/app.exe", "--float"], input="((((((((((((((((((((((((((((((((((((((((((((((((((2+((((((((((((((((((((((\n(((((((((((((((((\f(((5+((((((((((((((((((((((((((((((((((((((((((((0+9+(((((((((\n(((((((((((((((((((((((((((((((((((((((((((\n((((((((((((((((((((((((((((((((((((((((((((((((((((((((2*3))))))))))))))))))))))))))))))))))))))))))))))))))))))))\f)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))\n)))))))))))))))))))))))))))))))))))))))))))))))))))))))\f))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))",text=True,capture_output=True)
    assert res.returncode == 0
    assert float(res.stdout) == 22.0000

def test10():
    res=subprocess.run(["build/app.exe"], input="(2+1+((2*4)))",text=True,capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 11   

def test11():
    res=subprocess.run(["build/app.exe"], input="1/(2-2)",text=True,capture_output=True)
    assert res.returncode == 1
    assert str(res.stdout) == "unacceptable div argument(<=|0.0001|) -> exit(1)\n"  

def test12():
    res=subprocess.run(["build/app.exe"], input="1+1.5",text=True,capture_output=True)
    assert res.returncode == 2
    assert str(res.stdout) == "unacceptable symbol -> exit(2)\n"  

def test13():
    inp = ""
    for i in range(10):
        inp += "((((((((((((((((((((((((((((((((((((((((((((((((((2+((((((((((((((((((((((\n(((((((((((((((((\f(((5+((((((((((((((((((((((((((((((((((((((((((((0+9+(((((((((\n(((((((((((((((((((((((((((((((((((((((((((\n((((((((((((((((((((((((((((((((((((((((((((((((((((((((2*3))))))))))))))))))))))))))))))))))))))))))))))))))))))))\f)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))\n)))))))))))))))))))))))))))))))))))))))))))))))))))))))\f))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))+"
    inp += "((((((((((((((((((((((((((((((((((((((((((((((((((2+((((((((((((((((((((((\n(((((((((((((((((\f(((5+((((((((((((((((((((((((((((((((((((((((((((0+9+(((((((((\n(((((((((((((((((((((((((((((((((((((((((((\n((((((((((((((((((((((((((((((((((((((((((((((((((((((((2*3))))))))))))))))))))))))))))))))))))))))))))))))))))))))\f)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))\n)))))))))))))))))))))))))))))))))))))))))))))))))))))))\f))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))";
    res=subprocess.run(["build/app.exe"], input=inp,text=True,capture_output=True)
    assert res.returncode == 3
    assert str(res.stdout) == "too much symbols -> exit(3)\n"  

def test14():
    res=subprocess.run(["build/app.exe"], input="1000000000 * 2 + 1",text=True,capture_output=True)
    assert res.returncode == 4
    assert str(res.stdout) == "unacceptable number size(>|2 * 10^9|) -> exit(4)\n"  

def test15():
    res=subprocess.run(["build/app.exe"], input="123/(1/10000)",text=True,capture_output=True)
    assert res.returncode == 1
    assert str(res.stdout) == "unacceptable div argument(<=|0.0001|) -> exit(1)\n"  

def test16():
    res=subprocess.run(["build/app.exe"], input="1*(-2)",text=True,capture_output=True)
    assert res.returncode == 7
    assert str(res.stdout) == "two special symbols in a row! -> exit(7)\n"  

def test17():
    res=subprocess.run(["build/app.exe"], input="1+-2",text=True,capture_output=True)
    assert res.returncode == 7
    assert str(res.stdout) == "two special symbols in a row! -> exit(7)\n"  

def test18():
    res=subprocess.run(["build/app.exe"], input="+1 - 2",text=True,capture_output=True)
    assert res.returncode == 8
    assert str(res.stdout) == "input cant start with this symbol -> exit(8)\n"  
def test19():
    res=subprocess.run(["build/app.exe"], input="(2+1+(2*4)))",text=True,capture_output=True)
    assert res.returncode == 9
    assert str(res.stdout) == "brackets not correct! -> exit(9)\n"  

def test20():
    res=subprocess.run(["build/app.exe"], input="(2+1+(2 4)))",text=True,capture_output=True)
    assert res.returncode == 10
    assert str(res.stdout) == "no signs between two integers! -> exit(10)\n"  