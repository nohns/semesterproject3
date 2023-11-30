/** @format */

import { GiDrinkMe } from "react-icons/gi";

function Header(): JSX.Element {
  return (
    <div className=" text-white">
      <div className="flex flex-col items-center py-8">
        <h1 className="text-4xl md:text-6xl lg:text-7xl font-bold">
          {/* <AiOutlineStock className="inline-block mr-2 text-green-500" /> */}
          <GiDrinkMe className="inline-block mr-2 text-emerald-400" />

          <span className="text-emerald-400">DRINKS</span>
          <span className="text-rose-500">MACHINE</span>

          {/*   <AiOutlineStock
            className="inline-block ml-2 text-red-500"
            style={{ transform: "scaleX(-1)" }}
          /> */}
          <GiDrinkMe
            className="inline-block ml-2 text-rose-500"
            style={{ transform: "scaleX(-1)" }}
          />
        </h1>
        <p className="mt-2 text-lg font-mono">
          Your favorite way to configure your drinks
        </p>
      </div>
    </div>
  );
}

export default Header;
