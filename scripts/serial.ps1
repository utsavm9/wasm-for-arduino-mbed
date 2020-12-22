# Add to C:\Windows\System32\WindowsPowerShell\v1.0\profile.ps1
#   for function to be avaiable always in Powershell

# Use: Serial-Monitor
# Use: Serial-Monitor COM5 115200
# Ctrl-C to end it.
function Serial-Monitor {
    param(
        [Parameter(Mandatory=$false)]
        [String] $COMPort,

        [Parameter(Mandatory=$false)]
        [ValidateRange(0, 115200)]
        [Int] $BaudRate
    )

    if ((-not ($PSBoundParameters.ContainsKey('COMPort'))) -and (-not ($PSBoundParameters.ContainsKey('BaudRate')))) {
        echo "Usage: Serial-Monitor <COMPort> <BaudRate>"
        echo "  eg.: Serial-Monitor COM5 115200"
        echo ""
        echo "Getting name and device ID of COM Ports..."
        Get-CimInstance -Class Win32_SerialPort | Select-Object Name, Description, DeviceID
        return
    }

    echo "Exit with Ctrl-C"
    echo ""

    $port = new-Object System.IO.Ports.SerialPort $COMPort, $BaudRate, None, 8, one
    $port.ReadTimeOut = 1000;
    $port.Open()

    [console]::TreatControlCAsInput = $true

    do {

        if ([console]::KeyAvailable) {
            $key = [system.console]::readkey($true)
            if (($key.modifiers -band [consolemodifiers]"control") -and ($key.key -eq "C")) {
                echo "\nExititng"
                break;
            }
        }
        else {
            try {
                $line = $port.ReadLine()
                Write-Host $line 
            }
            catch {}
        }
    }
    while ($port.IsOpen)

    $port.Close()
}
