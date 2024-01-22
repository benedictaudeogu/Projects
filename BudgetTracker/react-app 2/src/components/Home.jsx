// create a home page that points to / path
import React, { useState, useEffect } from "react";
import { home } from "../services/BudgetServices";
import "../home.css";

export const Home = () => {
    useEffect(() => {
        console.log('Sending GET request...');
        home().then((response) => {
            console.log('Response received:', response.data);
        })
        .catch((error) => {
            console.error('Error:', error);
        });
    }, []); // The empty dependency array ensures the request is made once when the component mounts

    // return string printed in the response
    return (
        <>
            <h1>Welcome to the Budget Tracker!</h1>
            <button onClick={() => window.location.href = '/getInstitutions'}>View Institutions</button>
        </>
    )
}

export default Home;