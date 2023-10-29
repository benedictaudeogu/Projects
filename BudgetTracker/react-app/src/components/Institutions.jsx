import React, { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import { getInstitutionsService } from "../services/BudgetServices";

export const Institutions = () => {
    const [data, setData] = useState([]);

    useEffect(() => {
        console.log('Sending GET request...');
        getInstitutionsService().then((response) => {
            console.log('Response received:', response.data);
            setData(response.data)
            // parse response products into comma separated string
            response.data.forEach((institution) => {
                institution.products = institution.products.join(', ');
            });
        })
        .catch((error) => {
            console.error('Error:', error);
        });
    }, []); // The empty dependency array ensures the request is made once when the component mounts

    return (
        <>
            <table>
                <tbody>
                    <tr>
                        <th>Institution Id</th>
                        <th>Name</th>
                        <th>Products</th>
                        <th>Country Codes</th>
                        <th>Routing Numbers</th>
                    </tr>
                    {data.map((institution, key) => {
                        return (
                            <tr key={key}>
                                <td>{institution.institutionId}</td>
                                <td>{institution.name} </td>
                                <td>{institution.products}</td>
                                <td>{institution.countryCodes}</td>
                                <td>{institution.routingNumbers}</td>
                            </tr>
                        )
                    })}
                </tbody>
            </table>
            <button onClick={() => window.location.href = '/'}>Go back to homepage</button>
        </>
    )
}

export default Institutions;