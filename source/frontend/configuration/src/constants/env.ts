/** @format */

interface env {
  API_URL: string;
  MOCKED: boolean;
}

//Im lazy right now we need to read in from the .env file later
const ENV: env = {
  API_URL: import.meta.env.VITE_API_URL as string,
  MOCKED: import.meta.env.VITE_MOCKED as boolean,
};

export default ENV;
