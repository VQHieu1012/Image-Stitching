import shutil
from fastapi import FastAPI, File, HTTPException, UploadFile, Form
import os
import subprocess
from pydantic import ValidationError


app=FastAPI()

def validate_file_type(filename: str):
    allowed_extensions = ('.jpg', '.jpeg', '.png')
    ext = os.path.splitext(filename)[1]
    if ext.lower() not in allowed_extensions:
        raise HTTPException(status_code=422, detail="Only JPEG and PNG files allowed")

@app.post("/process-images")
async def process_images(img1: UploadFile=File(...), img2:UploadFile=File()):
    try:
        validate_file_type(img1.filename)
        validate_file_type(img2.filename)
        # Process image 1
        with open(f"{img1.filename}", "wb") as buffer:
            shutil.copyfileobj(img1.file, buffer)

        # Process image 2
        with open(f"{img2.filename}", "wb") as buffer:
            shutil.copyfileobj(img2.file, buffer)

        return {"message": "Images processed successfully"}
    except ValidationError as e:
        raise HTTPException(status_code=422, detail=str(e))
    except Exception as e:
        raise HTTPException(status_code=500, detail="Internal server error")
    
def run_wsl_command(command):
    try:
        completed_process = subprocess.run(
            ['wsl', command],
            capture_output=True,
            text=True,
            shell=True
        )
        
        # Check if the command was successful
        if completed_process.returncode == 0:
            return completed_process.stdout
        else:
            return completed_process.stderr

    except FileNotFoundError:
        return "WSL is not installed or not accessible."

# Example: Running 'ls' command in WSL
# output = run_wsl_command('ls')
# print(output)
