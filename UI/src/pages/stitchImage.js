// pages/about.js

import React, {useState, useRef} from "react";
import "../App.css";


const StitchImage = () => {
	const [image1, setImage1] = useState(null);
	const [image2, setImage2] = useState(null);
    const inputRef1 = useRef();
    const inputRef2 = useRef();

	const [stitchedImage,setStitchedImage] = useState(null);
	const handleImage1Change = (e) => {
		const file = e.target.files[0];
		if (file) {
			const reader = new FileReader();
			reader.onloadend = () => {
			console.log(file)
			setImage1(reader.result);
			};
			reader.readAsDataURL(file);	
		}
	};
  
	const handleImage2Change = (e) => {
		const file = e.target.files[0];
		if (file) {
			const reader = new FileReader();
			reader.onloadend = () => {
			setImage2(reader.result);
			};
			reader.readAsDataURL(file);
		}
	};

    const removeImage1 = () => {
        setImage1(null);
        if (inputRef1.current) {
            inputRef1.current.value = ''; // Resetting the input field value
        }
    };

    const removeImage2 = () => {
        setImage2(null);
        if (inputRef2.current) {
            inputRef2.current.value = ''; // Resetting the input field value
        }
    };

    

	const stitchingImages = async () => {
        
        if (!image1 || !image2) {
            // Handle case where both images are not selected
            window.alert('Please select both images before stitching.');
            return;
        }
        const formData = new FormData();

        formData.append('image1', image1);
        formData.append('image2', image2);
        
        try {
            const response = await fetch('/process-images', {
                method: 'POST',
                body: formData
            });

            const data = await response.json();

            setStitchedImage(data.stitchedImage);
        } catch (error) {
            let message = error.message;
            if(error.response) {
            // The request was made and the server responded with a status code
            // that falls out of the range of 2xx
                message = error.response.data.message; 
            } else if (error.request) {
                // The request was made but no response was received
                message = 'No response received';
            } else {
                // Something else happened in making the request  
                message = error.message;  
            }
            // Handle error
            window.alert(message);
        }
    };

    

	return (
		<div className="image-uploader">
                <div className="image-container">
                    <h2>Image 1</h2>
                    <input type="file" accept="image/jpg, image/jpeg, image/png" onChange={handleImage1Change} ref={inputRef1}/>
                    {image1 && (
                        <div>
                            <img src={image1} alt="" className="preview-img" />
                            <br/>
                            <button onClick={removeImage1}>Remove Image 1</button>
                        </div>
                    )}
                </div>
                <div className="image-container">
                    <h2>Image 2</h2>
                    <input type="file" accept="image/jpg, image/jpeg, image/png" onChange={handleImage2Change} ref={inputRef2}/>
                    {image2 && (
                        <div>
                            <img src={image2} alt="" className="preview-img" />
                            <br/>
                            <button onClick={removeImage2}>Remove Image 2</button>
                        </div>
                    )}
                </div>
            
			<button onClick={stitchingImages} className="stitch-button">Stitch Images</button>
			{stitchedImage && (
			<img src={stitchedImage} alt="Stitched" />
			)}
        </div>
		
	);
  };

export default StitchImage;
