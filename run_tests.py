import subprocess
import multiprocessing

def run_a_exe(arg):
    print(f"Running a.exe with argument {arg}")
    try:
        result = subprocess.run(['a.exe', arg], capture_output=True, text=True)
        if "Expected" in result.stdout:
            print(f"Output for {arg}:")
            print(result.stdout)
    except Exception as e:
        print(f"An error occurred while running a.exe with argument {arg}: {e}")

ignored_codes = []

def run_tests():
    cmds = []
    for i in range(0X00, 0x100):
        hex_value = f"CB {i:02X}"
        arg = f"..\\sm83\\v1\\{hex_value}.json"
    
        cmds.append(arg)
        
    with multiprocessing.Pool() as pool:
        pool.map(run_a_exe, cmds)
        
        
    
    
    
if __name__ == "__main__":
    run_tests()