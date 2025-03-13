# Stop any processes using files in the build directory (if necessary)
$buildPath = "build"

if (Test-Path $buildPath) {
    Write-Host "Stopping any processes using the build directory..."
    Get-Process | Where-Object { $_.Path -like "$PWD\$buildPath\*" } | Stop-Process -Force -ErrorAction SilentlyContinue

    Write-Host "Forcefully removing old build directory..."
    Remove-Item -Recurse -Force $buildPath -ErrorAction SilentlyContinue
    Start-Sleep -Seconds 1 # Allow time for removal
}

# Ensure the directory is fully removed
if (Test-Path $buildPath) {
    Write-Host "Failed to remove build directory!" -ForegroundColor Red
    exit 1
} else {
    Write-Host "Old build directory removed successfully."
}

# Create a new build directory
New-Item -ItemType Directory -Path $buildPath | Out-Null
Set-Location $buildPath

# Run CMake to configure the project with MinGW
Write-Host "Configuring project with CMake..."
cmake -G "MinGW Makefiles" ..

# Check if CMake succeeded
if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake configuration failed!" -ForegroundColor Red
    exit $LASTEXITCODE
}

# Build the project using MinGW32-make
Write-Host "Building project with MinGW32-make..."
mingw32-make

# Check if the build succeeded
if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit $LASTEXITCODE
}

Set-Location ..

Write-Host "Build completed successfully!" -ForegroundColor Green
