import "./App.css";
import NavBar from "./components/Navbar";
import { BrowserRouter as Router,  Route, Routes } from "react-router-dom";
import  Home  from "./pages";
import  StitchVideo  from "./pages/stitchVideo";
import  StitchImage  from "./pages/stitchImage";

function App() {
  return (
    <>
      <Router>
        <NavBar />

        <div className="pages">
          <Routes>
            <Route index element={<Home />} />
            <Route path="/stitchImage" element={<StitchImage />} />
            <Route path="/stitchVideo" element={<StitchVideo />} />
          </Routes>
        </div>
      </Router>
    </>
  );
}

export default App;