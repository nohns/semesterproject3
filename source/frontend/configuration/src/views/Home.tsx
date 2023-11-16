/** @format */

import useGetContainers from "@/api/endpoints/container/getContainers";
import useGetDrinks, { Drink } from "@/api/endpoints/drinks/getDrinks";
import useGetFluids, { Fluid } from "@/api/endpoints/fluid/getFluids";
import useGetImages, { Image } from "@/api/endpoints/images/getImages";
import { Button } from "@/components/ui/button";
import ShowFluid from "./fluid/ShowFluid";
import ShowDrink from "./drink/ShowDrink";
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
import {
  DropdownMenu,
  DropdownMenuItem,
  DropdownMenuTrigger,
  DropdownMenuContent,
  DropdownMenuLabel,
  DropdownMenuSeparator,
} from "@/components/ui/dropdown-menu";

import CustomDropdown from "@/components/Dropdown";
import FluidBackdrop from "@/components/ui/FluidBackdrop";

function Home(): JSX.Element {
  //De her 4 er hooks som der laver API kald
  //const images = useGetImages();
  //I kan kalde flere ting på dem de eneste som rigtigt er relevante er isLoading, isError og data
  //Altså om den er igang med at loade dataen stadig, om der er sket en fejl og så selve dataen

  //Nede I JSXen kan I så bruge de forskellige ting ofte bruger man conditional logik altså ternary operators(selvom det er noget pis) og så &&
  //Når man har et array så bruger man en funktion som hedder map til at loope henover dataen så kan man nemlig få flere ting til at render
  //Se neget i JSX'en

  //const fluids = useGetFluids();

  //const drinks = useGetDrinks();

  //const containers = useGetContainers();

  //Her tjekker vi altså for om dataen er loadet ind endnu, hvis den ikke er så viser vi bare en loading besked
  /*   if (
    images.isLoading ||
    fluids.isLoading ||
    drinks.isLoading ||
    containers.isLoading
  ) {
    return <div>Loading...</div>;
  } */

  /*   //Hvis i åbner browseren og trykker inspect så kan i åbne developer tooling hvor i kan finde consollen browseren der logger jeg dataen ud
  console.log(images.data?.images);
  console.log(fluids.data?.fluids);
  console.log(drinks.data?.drinks);
  console.log(containers.data?.containers); */

  //Mutation functions er til at lave POST, PUT, DELETE requests
  //De fungerer lidt anderledes ved at de først kører når man kalder .mutate på dem hvorimod query funktionerne vil køre lige med det samme

  //Lige noget test data for at validere magien
  const fluids: Fluid[] = [
    {
      id: 4,
      name: "Vodka",
    },
    {
      id: 5,
      name: "Rom",
    },
    {
      id: 2,
      name: "Blå booster",
    },
    {
      id: 3,
      name: "Vand",
    },
    {
      id: 1,
      name: "Coca Cola",
    },
  ];

  //Den her funktion returnerer et object calc som udelukkende returnerer en funktion som hedder calculate som kan bruges til at beregne drinks kombinationer
  const calc = useCalculateDrinks();

  //Så her kan man jo så kalde calculate med et array af fluids, det er så meningen at jeres dropdown menuer skal tilføje noget state som danner et array af fluid arrays :)
  //Umiddelbart ville jeg bruge en useEffect hook hvor dependency arrayet er et array af jeres state arrays så kan i bare kalde calculate i useEffecten
  const possibleDrinks = calc?.calculate(fluids);
  console.log(possibleDrinks);
  //Så ville jeg lave et komponent som tager imod en drink og displayer den

  //Her kan i se at jeg bruger .map på data.images som jo er et array så kan vi render 3 billeder slef
  return (
    <>
      <div className="flex flex-col items-center">
        <Header />
        <div className="flex flex-col items-center mt-[-50px]">
          <div className="flex flex-row justify-center space-x-7 mt-10">
            <FluidBackdrop />
            <FluidBackdrop />
            <FluidBackdrop />
          </div>
          <div className="bg-emerald-600 mt-5 py-12  px-80 rounded-2xl transition duration-300 hover:bg-emerald-600 hover:darken-2 hover:opacity-75">
            Possible drink possibilities
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
