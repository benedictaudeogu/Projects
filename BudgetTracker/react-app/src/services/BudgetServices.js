import axios from "axios";

//global variable for the base url
const baseUrl = "http://localhost:8080";

export const home = () => {
  return axios.get(`${baseUrl}`);
};

export const getInstitutionsService = () => {
    return axios.get(`${baseUrl}/getInstitutions`);
};

export const getTransactionsService = () => {
    return axios.get(`${baseUrl}/getTransactions`);
}


