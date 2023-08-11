import Foundation

func isHwinfoRunning() -> Bool {
    let task = Process()
    task.launchPath = "/bin/ps"
    task.arguments = ["axco", "comm"]
    
    let pipe = Pipe()
    task.standardOutput = pipe
    task.launch()
    
    let data = pipe.fileHandleForReading.readDataToEndOfFile()
    if let output = String(data: data, encoding: .utf8) {
        return output.contains("HWiNFO64.EXE")
    }
    
    return false
}

func openHwinfo() {
    if !isHwinfoRunning() {
        let hwinfoPath = "/Applications/HWiNFO64.EXE"  // Path may need adjustment
        let task = Process()
        task.launchPath = "/usr/bin/open"
        task.arguments = [hwinfoPath]
        task.launch()
        
        print("HWiNFO64.EXE is opened.")
    } else {
        print("HWiNFO64.EXE is already running.")
    }
}

func killHwinfo() {
    let task = Process()
    task.launchPath = "/usr/bin/killall"
    task.arguments = ["HWiNFO64.EXE"]
    task.launch()
    task.waitUntilExit()
    
    if task.terminationStatus == 0 {
        print("HWiNFO64.EXE process terminated.")
    } else {
        print("HWiNFO64.EXE process is not running.")
    }
}

func main() {
    // First, kill the HWiNFO64 process if it's running
    killHwinfo()

    // Add a small delay (in seconds)
    sleep(1)  // You can adjust the duration as needed

    // Then, open the HWiNFO64 process
    openHwinfo()
}

main()
