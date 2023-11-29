/** @format */

import { Button } from "@/components/ui/button";
import {
  AlertDialog,
  AlertDialogAction,
  AlertDialogCancel,
  AlertDialogContent,
  AlertDialogDescription,
  AlertDialogFooter,
  AlertDialogHeader,
  AlertDialogTitle,
  AlertDialogTrigger,
} from "@/components/ui/alert-dialog";
import { useState } from "react";

import { Input } from "@/components/ui/input";

import { Progress } from "@/components/ui/progress";
import CustomAlertDialogAction from "@/components/CustomAlertDialogAction";
import useCreateDrink from "@/api/endpoints/drinks/createDrink";
import useCreateFluid from "@/api/endpoints/fluid/createFluid";
import useGetFluids, { Fluid } from "@/api/endpoints/fluid/getFluids";
import { Card, CardContent, CardTitle } from "@/components/ui/card";
import { Drink, Ingredient } from "@/api/endpoints/drinks/getDrinks";
import useGetImages, { Image } from "@/api/endpoints/images/getImages";

enum GuideState {
  step1 = 10,
  step2 = 11,
  step3 = 30,
  step4 = 50,
  step5 = 65,
  step6 = 75,
  step7 = 100,
}

interface CreateDrinkGuideProps {}

function CreateDrinkGuide({}: CreateDrinkGuideProps) {
  //I want to do a switch statement on html content so we can have different guides for different steps

  const [step, setStep] = useState<GuideState>(GuideState.step1);

  const handleStep = () => {
    //Increment step to the next possible enum value
    const nextStep = (Object.values(GuideState) as GuideState[]).find(
      (stepValue: GuideState) => stepValue > step
    );

    if (nextStep) {
      setStep(nextStep);
    }
  };

  const fluids = useGetFluids();
  const createDrink = useCreateDrink();
  const createFluid = useCreateFluid();
  const images = useGetImages();

  const [fluidName, setFluidName] = useState("");

  const handleSubmitFluid = () => {
    setStep(GuideState.step1);
    console.log("Calling mutate for create fluid");
    createFluid.mutate({ name: fluidName });
  };

  const [selectedFluids, setSelectedFluids] = useState<Fluid[]>([]);

  const handleFluidSelection = (fluid: Fluid) => {
    if (selectedFluids.some((selectedFluid) => selectedFluid.id === fluid.id)) {
      // Deselect the fluid
      setSelectedFluids(
        selectedFluids.filter((selectedFluid) => selectedFluid.id !== fluid.id)
      );
    } else if (selectedFluids.length < 3) {
      // Select the fluid if less than 3 are already selected
      setSelectedFluids([...selectedFluids, fluid]);
    }
  };

  const [ingredients, setIngredients] = useState<Ingredient[]>([]);

  const handleCLChange = (fluid: Fluid, clAmount: number, i: number) => {
    //Set ingredient of index i equal to the fluid and cl amount
    const newIngredient: Ingredient = { fluid: fluid, amountInCl: clAmount };
    const newIngredients = [...ingredients];
    newIngredients[i] = newIngredient;
    setIngredients(newIngredients);
  };

  const [selectedImage, setSelectedImage] = useState<Image | undefined>(
    undefined
  );

  const [drinkName, setDrinkName] = useState("");

  const [newDrink, setNewDrink] = useState<Drink | undefined>(undefined);

  //Function which creates a drink object based on values provided
  const handleSubmitDrink = () => {
    //Combine all of the state into a drink object

    const drink: Drink = {
      name: drinkName,
      ingredients: ingredients,
      //@ts-ignore
      image: selectedImage,
    };
    console.log(drink);
    createDrink.mutate(drink);

    setStep(GuideState.step1);
  };

  //Steps passer ikke rigtigt med hvad der skal ske
  const renderView = () => {
    switch (step) {
      case GuideState.step1:
        return (
          <div className="flex flex-col gap-2">
            <div>
              Lets help you add a new drink to the catalogue! These are the
              currently available fluids
            </div>
            <div className="border p-2 m-1">
              {fluids.data?.fluids.map((fluid) => (
                <li className="">{fluid.name}</li>
              ))}
            </div>

            <div className="flex flex-row gap-4 my-2">
              <Button onClick={() => setStep(GuideState.step2)}>
                Create new fluid
              </Button>
              <Button onClick={() => setStep(GuideState.step3)}>
                Create new drink
              </Button>
            </div>
          </div>
        );

      case GuideState.step2:
        return (
          <div className="flex flex-col gap-2">
            <div>What would you like to name the fluid?</div>

            <div className="flex flex-row gap-4 my-2">
              <Input
                onChangeCapture={(e) =>
                  setFluidName((e.target as HTMLInputElement).value)
                }
                inputMode="text"
                required={true}
                placeholder="Name of the fluid"
                type="email"
              ></Input>
              <Button className="" onClick={handleSubmitFluid}>
                Next
              </Button>
            </div>
          </div>
        );
      case GuideState.step3:
        return (
          <div className="flex flex-col gap-2">
            <div>What would you like to name the drink?</div>

            <div className="flex flex-row gap-4 my-2">
              <Input
                onChangeCapture={(e) =>
                  setDrinkName((e.target as HTMLInputElement).value)
                }
                inputMode="text"
                required={true}
                placeholder="Name of the drink"
                type="email"
              ></Input>
              <Button className="" onClick={() => setStep(GuideState.step4)}>
                Next
              </Button>
            </div>
          </div>
        );
      case GuideState.step4:
        return (
          <div>
            <div>Select fluids for your drink</div>
            {fluids.data?.fluids.map((fluid) => (
              <div
                key={fluid.id}
                className={`flex flex-row gap-4 my-auto self-center border p-4 mt-2 ${
                  selectedFluids.some(
                    (selectedFluid) => selectedFluid.id === fluid.id
                  )
                    ? "bg-gray-200 text-black"
                    : ""
                }`}
                onClick={() => handleFluidSelection(fluid)}
              >
                {fluid.name}
              </div>
            ))}

            {/*Error msg for no selected fluids*/}
            {selectedFluids.length === 0 && (
              <div> Error: You must select a minimum of 1 fluid</div>
            )}
            <Button
              className="mt-4"
              disabled={selectedFluids.length > 3}
              onClick={() => setStep(GuideState.step5)}
            >
              Next
            </Button>
          </div>
        );
      case GuideState.step5:
        return (
          <div>
            <div>Choose the amount of fluids in your drink </div>
            {selectedFluids.map((selectedFluid, i) => (
              <div
                key={selectedFluid.id}
                className="flex flex-row gap-4 my-auto self-center border p-4 mt-2"
              >
                <span className="my-auto w-32">{selectedFluid.name}</span>
                <Input
                  placeholder="Amount in cl"
                  type="number"
                  onChange={(e) =>
                    /* @ts-ignore */
                    handleCLChange(selectedFluid!, e.target.value, i)
                  }
                ></Input>
              </div>
            ))}
            <Button
              disabled={ingredients.length !== selectedFluids.length}
              className="mt-4"
              onClick={() => setStep(GuideState.step6)}
            >
              Next
            </Button>
          </div>
        );

      case GuideState.step6:
        const drinkImages = images.data?.images.filter(
          (image) => image.id <= 3
        );

        return (
          <div>
            <div>Choose an image for your drink</div>
            <div className="flex my-2">
              {drinkImages?.map((image) => (
                <div>
                  <img
                    src={image.path}
                    className={`w-20 h-20  ${
                      selectedImage?.id === image.id
                        ? "bg-gray-200 text-black"
                        : ""
                    }`}
                    onClick={() => setSelectedImage(image)}
                  />
                </div>
              ))}
              <Button
                className="my-auto ml-4"
                onClick={() => setStep(GuideState.step7)}
              >
                Next
              </Button>
            </div>
          </div>
        );

      case GuideState.step7:
        return (
          <div>
            <div>Do you want to create this drink?</div>
            <div className="flex flex-col gap-2">
              <div>Name: {drinkName}</div>
              <div>Ingredients:</div>
              <div className="flex flex-col gap-2">
                {ingredients.map((ingredient) => (
                  <div className="flex flex-row gap-4 my-auto  border p-4 mt-2">
                    <span className="my-auto w-32">
                      {ingredient.fluid.name}
                    </span>
                    <span>{ingredient.amountInCl} cl</span>
                  </div>
                ))}
              </div>
              <div>Image:</div>
              <div>
                <img src={selectedImage?.path} className="w-20 h-20" />
              </div>
            </div>
          </div>
        );
      default:
        return <div>Something went wrong :/</div>;
    }
  };

  return (
    <>
      <AlertDialog>
        <AlertDialogTrigger className="py-10 px-16">
          Add to menu
        </AlertDialogTrigger>
        <AlertDialogContent className="">
          <AlertDialogHeader>
            <AlertDialogTitle>Configuration guide</AlertDialogTitle>
            <AlertDialogDescription>{renderView()}</AlertDialogDescription>
          </AlertDialogHeader>
          <AlertDialogFooter>
            {step === GuideState.step7 && (
              <CustomAlertDialogAction onClose={() => handleSubmitDrink()}>
                Finish
              </CustomAlertDialogAction>
            )}
          </AlertDialogFooter>
          <Progress value={step} />
        </AlertDialogContent>
      </AlertDialog>
    </>
  );
}

export default CreateDrinkGuide;
