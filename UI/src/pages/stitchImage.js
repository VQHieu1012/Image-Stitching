import React, { useState } from 'react';
import { ImageUploader } from './ImageUploader';

const StitchImage = () => {
  const [stitchedImage, setStitchedImage] = useState(null);
  const [files, setFiles] = useState([null, null]);

  const stitchingImages = async () => {
    if (!files.every(Boolean)) {
      window.alert('Please select both images before stitching.');
      return;
    }

    const formData = new FormData();
    formData.append('img1', files[0]);
    formData.append('img2', files[1]);

    try {
      const response = await fetch('/process-images', {
        method: 'POST',
        body: formData,
      });

      if (!response.ok) {
        throw new Error('Image stitching failed');
      }

      const data = await response.json();
      setStitchedImage(data.stitchedImage);
    } catch (error) {
      window.alert(error.message);
    }
  };

  return (
    <div className="image-uploader">
      {[0, 1].map((index) => (
        <ImageUploader
          key={index}
          index={index}
          onFileChange={(file) => {
            setFiles((prevFiles) => {
              const newFiles = [...prevFiles];
              newFiles[index] = file;
              return newFiles;
            });
          }}
        />
      ))}
      <button onClick={stitchingImages} className="stitch-button">
        Stitch Images
      </button>
      {stitchedImage && <img src={stitchedImage} alt="Stitched" />}
    </div>
  );
};

export default StitchImage;