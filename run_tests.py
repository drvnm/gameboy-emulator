import subprocess

def run_a_exe(arg):
    try:
        result = subprocess.run(['a.exe', arg], capture_output=True, text=True)
        if "Expected" in result.stdout:
            print(f"Output for {arg}:")
            print(result.stdout)
    except Exception as e:
        print(f"An error occurred while running a.exe with argument {arg}: {e}")

ignored_codes = [0x10, 0x10]

def main():
    for i in range(0x86, 0x100):
        hex_value = f"{i:02X}"
        arg = f"..\\sm83\\v1\\CB {hex_value}.json"
        if i not in ignored_codes:
            print(f"Running a.exe with argument {arg}")
            run_a_exe(arg)

if __name__ == "__main__":
    main()
