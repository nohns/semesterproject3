/** @format */
//import { AiOutlineStock } from "react-icons/ai";
import { GiDrinkMe } from "react-icons/gi";
export default function Footer(): JSX.Element {
  return (
    <footer className="px-4 pb-2 mt-auto">
      <div className="text-xl font-bold whitespace-nowrap text-white flex items-center justify-left pl-4 pr-4">
        <GiDrinkMe className="h-6 w-6 mr-2 text-white" />
        DRINKSMACHINE
      </div>
      <hr className="my-3 sm:mx-auto bg-red-500" />

      <span className="block text-s text-white sm:text-center mb-1">
        <p>
          <strong>Contact info:</strong>
        </p>
        <p>Email: contact@drinksmachine.com</p>
        <p>Phone: (45) 11111111</p>
      </span>
      <span className="block text-xs text-white sm:text-center ">
        © 2023 DRINKSMACHINE™
      </span>
    </footer>
  );
}
