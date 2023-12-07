// pages/index.js

import React from 'react';
import example from '../images/stitching_example.jpg';
const Home = () => {
return (
	<div
		style={{
			justifyContent: 'center',
		}}
		>
		<h3>Application used <br/> for image stitching</h3>
		<img src={example} style={{maxWidth: '100%', height: 'auto'}} alt='example'/>
		
	</div>
	
);
};

export default Home;
