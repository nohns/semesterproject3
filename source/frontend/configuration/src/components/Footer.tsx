/** @format */

//import { AiOutlineStock } from "react-icons/ai";
import { GiDrinkMe } from "react-icons/gi";

export default function Footer(): JSX.Element {
  return (
    <footer className="px-6 pb-4 w-screen mt-auto">
      <div className="text-1xl font-bold whitespace-nowrap text-white flex items-center justify-between pl-14 pr-14">
        <div className=" flex items-center text-white">
          {/* <AiOutlineStock className="h-8 w-8 mr-2 text-black" /> */}
          <GiDrinkMe className="h-8 w-8 mr-2 text-white" />
          DRINKSMACHINE
        </div>

        <div>
          <div className="flex flex-col items-center"></div>
          <div className="flex justify-center align-middle"></div>
        </div>

        <div className=" flex items-center text-white invisible">
          {/*   <AiOutlineStock className="h-8 w-8 mr-2 text-black" /> */}
          DRINKSMACHINE
        </div>
      </div>

      <hr className="my-3 sm:mx-auto bg-red-500" />

      <span className="block text-sm text-gray-400 sm:text-center ">
        © 2023 DRINKSMACHINE™
      </span>
    </footer>
  );
}
