/** @format */

import useGetContainers, {
  FluidContainer,
} from "@/api/endpoints/container/getContainers";

import useCalculateDrinks from "@/hooks/CalculateDrinks";
import Header from "@/components/Header";
import Footer from "@/components/Footer";

import FluidBackdrop from "@/components/FluidBackdrop";
import { useEffect, useState } from "react";
import useGetDrinks, { Drink } from "@/api/endpoints/drinks/getDrinks";
import DrinkCard from "@/components/DrinkCard";
import useChangeContainer from "@/api/endpoints/container/changeContainer";
import useGetFluids from "@/api/endpoints/fluid/getFluids";

import { Button } from "@/components/ui/button";
import { Card } from "@/components/ui/card";
import CreateDrinkGuide from "./CreateDrinkGuide";
import ChangeContainerGuide from "./ChangeContainerGuide";
import DeleteDrinkGuide from "./DeleteDrinkGuide";

function Home(): JSX.Element {
  const fluids = useGetFluids();
  const drinks = useGetDrinks();
  const getContainers = useGetContainers();
  const changeContainer = useChangeContainer();

  const calc = useCalculateDrinks();

  const [possibleDrinks, setPossibleDrinks] = useState<Drink[] | undefined>([]);

  const [container1, setContainer1] = useState<FluidContainer>({
    id: 0,
    fluid: {
      id: 0,
      name: "Vælg væske",
    },
    fluidAmountInCl: 0,
  });
  const [container2, setContainer2] = useState<FluidContainer>({
    id: 0,
    fluid: {
      id: 0,
      name: "Vælg væske",
    },
    fluidAmountInCl: 50,
  });
  const [container3, setContainer3] = useState<FluidContainer>({
    id: 0,
    fluid: {
      id: 0,
      name: "Vælg væske",
    },
    fluidAmountInCl: 100,
  });

  useEffect(() => {
    if (getContainers.isLoading) {
      return;
    }
    setContainer1(getContainers.data?.containers![0]!);
    setContainer2(getContainers.data?.containers![1]!);
    setContainer3(getContainers.data?.containers![2]!);
  }, [getContainers.isLoading]);

  //Den her react funktion bliver kaldt hver gang at container1, container2 eller container3 ændrer sig dvs hvis i ændrer jeres dropdown menuer så vil den her funktion blive kaldt
  //Og så genberegner den mulige drinks
  useEffect(() => {
    if (
      drinks.isLoading ||
      fluids.isLoading ||
      getContainers.isLoading ||
      drinks.isError ||
      fluids.isError ||
      getContainers.isError
    ) {
      return;
    }
    console.log("Beregner en ny combination af drinks");

    const combinations = [container1.fluid, container2.fluid, container3.fluid];

    setPossibleDrinks(calc?.calculate(combinations, drinks.data?.drinks!));

    //possibleDrinks = calc?.calculate(combinations);
    console.log(possibleDrinks);
  }, [container1, container2, container3]);

  const handleChangeContainer = (e: React.MouseEvent) => {
    e.preventDefault();
    changeContainer.mutate({
      id: container1.id,
      newFluidId: container1.fluid.id!,
    });
    changeContainer.mutate({
      id: container2.id,
      newFluidId: container2.fluid.id!,
    });
    changeContainer.mutate({
      id: container3.id,
      newFluidId: container3.fluid.id!,
    });
  };

  if (fluids.isError || getContainers.isError || drinks.isError) {
    //if the endpoint is in error state then show a div with the error message
    return (
      <>
        {fluids.isError && (
          <div className="text-white text-5xl">"Error loading fluid data"</div>
        )}
        {getContainers.isError && (
          <div className="text-white text-5xl">
            "Error loading container data"
          </div>
        )}
        {drinks.isError && (
          <div className="text-white text-5xl">"Error loading drink data"</div>
        )}
      </>
    );
  }

  //Hvis der ikke er nogen fluids så kan vi ikke loade UI'et så vi returnerer bare en loading tekst
  if (fluids.isLoading || getContainers.isLoading || drinks.isLoading) {
    return <div className="text-black text-9xl">Loading...</div>;
  }

  //Hernede bliver alt magien samplet
  return (
    <>
      <div className="flex flex-col items-center ">
        <Header />
        <div className="flex flex-col items-center">
          <Card className="py-10 px-20 bg-zinc-400 w-full flex flex-col">
            <h1 className="mx-auto text-white font-mono text-6xl font-bold mt-2">
              Drinks calculator
            </h1>
            <h6 className="mx-auto text-white font-mono text-sm ">
              Click the containers to select new fluids and calculate possible
              drink combinations!
            </h6>
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
            <h6 className="flex flex-col items-center text-white font-mono text-2xl mt-2 ">
              Possible drinks
              {possibleDrinks && <DrinkCard drinks={possibleDrinks} />}
            </h6>
          </Card>
          <Card className="py-6 px-20 bg-zinc-400 mt-8 w-full flex flex-row justify-between gap-6">
            <div className="w-72 rounded-3xl bg-emerald-500  text-center text-white font-mono transition duration-300 hover:bg-teal-500">
              <CreateDrinkGuide />
            </div>
            <div className="bg-emerald-500 rounded-3xl w-72 text-center text-white font-mono transition duration-300 hover:bg-teal-500">
              <ChangeContainerGuide />
            </div>
            <div className="bg-emerald-500 rounded-3xl w-72 text-center text-white font-mono transition duration-300 hover:bg-teal-500">
              <DeleteDrinkGuide />
            </div>
          </Card>
        </div>
      </div>

      <Footer />
    </>
  );
}

export default Home;
