import React, { useState, useRef } from 'react';

export const ImageUploader = ({ index, onFileChange }) => {
    const [image, setImage] = useState(null);
    const [file, setFile] = useState(null);
    const fileInput = useRef();

    const handleImageChange = (e) => {
        const file = e.target.files[0];
        if (file) {
            setImage(URL.createObjectURL(file));
            setFile(file);
            onFileChange(file);
        }
    };

    const removeImage = () => {
        setImage(null);
        setFile(null);
        onFileChange(null);
        fileInput.current.value = null;
    };

    return (
        <div className="image-container">
            <h2>{`Image ${index + 1}`}</h2>
            <input type="file" onChange={handleImageChange} ref={fileInput} />
            {image && (
                <div>
                    <img src={image} alt="" className="preview-img" />
                    <br />
                    <button onClick={removeImage}>{`Remove Image ${index + 1}`}</button>
                </div>
            )}
        </div>
    );
};