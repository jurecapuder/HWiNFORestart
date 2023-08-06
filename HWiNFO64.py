import subprocess
import psutil
import time

def is_hwinfo_running():
    for process in psutil.process_iter(['name']):
        if "HWiNFO64.EXE" in process.info['name']:
            return True
    return False

def open_hwinfo():
    try:
        if not is_hwinfo_running():
            subprocess.Popen(["C:\\Program Files\\HWiNFO64\\HWiNFO64.EXE"])
            print("HWiNFO64.EXE is opened.")
        else:
            print("HWiNFO64.EXE is already running.")
    except Exception as e:
        print("An error occurred:", e)

def kill_hwinfo():
    try:
        # Check if HWiNFO64.EXE process is running
        for process in psutil.process_iter(['pid', 'name']):
            if "HWiNFO64.EXE" in process.info['name']:
                # Terminate the HWiNFO64.EXE process
                subprocess.run(["taskkill", "/F", "/IM", "HWiNFO64.EXE"])
                print("HWiNFO64.EXE process terminated.")
                break
        else:
            print("HWiNFO64.EXE process is not running.")

    except Exception as e:
        print("An error occurred:", e)

if __name__ == "__main__":
    # First, kill the HWiNFO64 process if it's running
    kill_hwinfo()

    # Add a small delay (in seconds)
    time.sleep(1)  # You can adjust the duration as needed

    # Then, open the HWiNFO64 process
    open_hwinfo()
