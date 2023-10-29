import './App.css';
import React, { useState, useEffect } from "react";
import {Route, Routes} from 'react-router-dom';
import Home from "./components/Home";
import Institutions from "./components/Institutions";

function App() {
    return (
        <>
        <Routes>
            <Route>
                <Route path="/" element={<Home/>} />
                <Route path="/getInstitutions" element={<Institutions/>} />
            </Route>
        </Routes>
        </>
    );
}
// element = {<WithNav/>}
export default App;