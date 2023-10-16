/** @format */

import { FaSpinner } from "react-icons/fa";

/* const Spinner = () => {
  return (
    <div className="flex flex-col items-center justify-center self-center">
      <FaSpinner className="animate-spin h-16 w-16 text-white " />
    </div>
  );
}; */

const Spinner = () => {
  return (
    <div className="fixed inset-0 flex items-center justify-center">
      <FaSpinner className="animate-spin h-16 w-16 text-white " />
    </div>
  );
};

export default Spinner;
