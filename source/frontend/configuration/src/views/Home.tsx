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
import FluidBackdrop from "@/components/ui/FluidBackdrop";

function Home(): JSX.Element {
  const fluids = useGetFluids();

  const calc = useCalculateDrinks();
  let possibleDrinks = calc?.calculate(fluids.data?.fluids!);

  //const drinks = useGetDrinks();

  //const containers = useGetContainers();

  //Lige noget test data for at validere magien
  /*   const fluids: Fluid[] = [
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
  ]; */

  //Den her funktion returnerer et object calc som udelukkende returnerer en funktion som hedder calculate som kan bruges til at beregne drinks kombinationer
  //Så her kan man jo så kalde calculate med et array af fluids, det er så meningen at jeres dropdown menuer skal tilføje noget state som danner et array af fluid arrays :)
  //Umiddelbart ville jeg bruge en useEffect hook hvor dependency arrayet er et array af jeres state arrays så kan i bare kalde calculate i useEffecten

  console.log(possibleDrinks);
  //Så ville jeg lave et komponent som tager imod en drink og displayer den

  const [container1, setContainer1] = useState<Fluid>();
  const [container2, setContainer2] = useState<Fluid>();
  const [container3, setContainer3] = useState<Fluid>();

  //Den her react funktion bliver kaldt hver gang at container1, container2 eller container3 ændrer sig dvs hvis i ændrer jeres dropdown menuer så vil den her funktion blive kaldt
  //Og så genberegner den mulige drinks
  useEffect(() => {
    console.log("Beregner en ny combination af drinks");
    possibleDrinks = calc?.calculate(fluids.data?.fluids!);
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
            <FluidBackdrop />
            <FluidBackdrop />
            <FluidBackdrop />
          </div>
          <div className="bg-emerald-600 mt-5 py-12  px-80 rounded-2xl transition duration-300 hover:bg-emerald-600 hover:darken-2 hover:opacity-75">
            Possible drink possibilities
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
