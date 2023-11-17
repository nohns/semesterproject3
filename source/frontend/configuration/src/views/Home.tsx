/** @format */

import useGetContainers from "@/api/endpoints/container/getContainers";

import useGetFluids, { Fluid } from "@/api/endpoints/fluid/getFluids";
import useGetImages, { Image } from "@/api/endpoints/images/getImages";

import ShowDrinks from "./drink/ShowDrinks";
import ShowImage from "./image/ShowImage";
import CreateDrinkButton from "./drink/CreateDrinkButton";
import CreateFluidButton from "./fluid/CreateFluidButton";
import useCreateFluid, {
  CreateFluidRequest,
} from "@/api/endpoints/fluid/createFluid";
import useCreateDrink, {
  CreateDrinkRequest,
  Ingredient,
} from "@/api/endpoints/drinks/createDrink";

import useCalculateDrinks from "@/hooks/CalculateDrinks";
import Header from "@/components/Header";
import Footer from "@/components/Footer";

import CustomDropdown from "@/components/Dropdown";
import FluidBackdrop from "@/components/FluidBackdrop";
import { useEffect, useState } from "react";
import { Drink } from "@/api/endpoints/drinks/getDrinks";

function Home(): JSX.Element {
  const fluids = useGetFluids();

  const calc = useCalculateDrinks();
  //Jeg mangler stadig at gøre default staten til whatever som vi læser ind fra fluid containersne
  const [possibleDrinks, setPossibleDrinks] = useState<Drink[]>();

  //let possibleDrinks = calc?.calculate(fluids.data?.fluids!);

  const [container1, setContainer1] = useState<Fluid>({
    id: 0,
    name: "Vælg væske",
  });
  const [container2, setContainer2] = useState<Fluid>({
    id: 0,
    name: "Vælg væske",
  });
  const [container3, setContainer3] = useState<Fluid>({
    id: 0,
    name: "Vælg væske",
  });

  //Den her react funktion bliver kaldt hver gang at container1, container2 eller container3 ændrer sig dvs hvis i ændrer jeres dropdown menuer så vil den her funktion blive kaldt
  //Og så genberegner den mulige drinks
  useEffect(() => {
    console.log("Beregner en ny combination af drinks");
    const combinations = [container1, container2, container3];
    setPossibleDrinks(calc?.calculate(combinations));

    //possibleDrinks = calc?.calculate(combinations);
    console.log(possibleDrinks);
  }, [container1, container2, container3]);

  //Hvis der ikke er nogen fluids så kan vi ikke loade UI'et så vi returnerer bare en loading tekst
  if (fluids.isLoading) {
    return <div>Loading...</div>;
  }

  //Hernede bliver alt magien samplet
  return (
    <>
      <div className="flex flex-col items-center">
        <Header />
        <div className="flex flex-col items-center mt-[-50px]">
          <div className="flex flex-row justify-center space-x-7 mt-10">
            <FluidBackdrop
              container={container1!}
              setContainer={setContainer1}
              fluids={fluids.data?.fluids!}
            />
            <FluidBackdrop
              container={container2!}
              setContainer={setContainer2}
              fluids={fluids.data?.fluids!}
            />
            <FluidBackdrop
              container={container3!}
              setContainer={setContainer3}
              fluids={fluids.data?.fluids!}
            />
          </div>
          <div className="flex flex-col items-center text-white font-mono text-xl">
            Possible drinks:
            {possibleDrinks && <ShowDrinks drinks={possibleDrinks!} />}
          </div>
          <div className="bg-pink-800 mt-5 py-4 px-8 rounded-2xl transition duration-300 hover:bg-pink-800 hover:darken-2 hover:opacity-75">
            Configure drink
          </div>
        </div>
        <Footer />
      </div>
      {/* </div> */}
      <Footer />
    </>
  );
}

export default Home;
