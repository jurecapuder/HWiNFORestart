const { exec } = require('child_process');
const psList = require('ps-list');
const os = require('os');

async function isHwinfoRunning() {
    const processes = await psList();
    return processes.some(process => process.name === 'HWiNFO64.EXE');
}

function openHwinfo() {
    if (!isHwinfoRunning()) {
        const hwinfoPath = 'C:\\Program Files\\HWiNFO64\\HWiNFO64.EXE';
        exec(`start "" "${hwinfoPath}"`, (error, stdout, stderr) => {
            if (error) {
                console.error('An error occurred:', error);
            } else {
                console.log('HWiNFO64.EXE is opened.');
            }
        });
    } else {
        console.log('HWiNFO64.EXE is already running.');
    }
}

function killHwinfo() {
    psList().then(processes => {
        const hwinfoProcess = processes.find(process => process.name === 'HWiNFO64.EXE');
        if (hwinfoProcess) {
            exec(`taskkill /F /PID ${hwinfoProcess.pid}`, (error, stdout, stderr) => {
                if (error) {
                    console.error('An error occurred:', error);
                } else {
                    console.log('HWiNFO64.EXE process terminated.');
                }
            });
        } else {
            console.log('HWiNFO64.EXE process is not running.');
        }
    });
}

async function main() {
    // First, kill the HWiNFO64 process if it's running
    await killHwinfo();

    // Add a small delay (in milliseconds)
    await new Promise(resolve => setTimeout(resolve, 1000));  // You can adjust the duration as needed

    // Then, open the HWiNFO64 process
    openHwinfo();
}

main();
