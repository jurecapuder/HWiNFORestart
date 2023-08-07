require 'open3'
require 'time'

def is_hwinfo_running
  processes = `tasklist`
  processes.include?('HWiNFO64.EXE')
end

def open_hwinfo
  unless is_hwinfo_running
    system('start "" "C:\\Program Files\\HWiNFO64\\HWiNFO64.EXE"')
    puts 'HWiNFO64.EXE is opened.'
  else
    puts 'HWiNFO64.EXE is already running.'
  end
end

def kill_hwinfo
  if is_hwinfo_running
    system('taskkill /F /IM HWiNFO64.EXE')
    puts 'HWiNFO64.EXE process terminated.'
  else
    puts 'HWiNFO64.EXE process is not running.'
  end
end

if __FILE__ == $PROGRAM_NAME
  # First, kill the HWiNFO64 process if it's running
  kill_hwinfo

  # Add a small delay (in seconds)
  sleep 1 # You can adjust the duration as needed

  # Then, open the HWiNFO64 process
  open_hwinfo
end
