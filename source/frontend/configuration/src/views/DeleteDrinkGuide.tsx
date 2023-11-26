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

import { Progress } from "@/components/ui/progress";
import CustomAlertDialogAction from "@/components/CustomAlertDialogAction";
import useDeleteDrink from "@/api/endpoints/drinks/deleteDrink";
import useDeleteFluid from "@/api/endpoints/fluid/deleteFluid";
import useGetFluids from "@/api/endpoints/fluid/getFluids";
import useGetDrinks from "@/api/endpoints/drinks/getDrinks";

enum GuideState {
  step1 = 10,
  step2 = 25,
  step3 = 50,
  step4 = 75,
}

interface DeleteDrinkGuideProps {}

function DeleteDrinkGuide({}: DeleteDrinkGuideProps) {
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

  const deleteDrink = useDeleteDrink();
  const deleteFluid = useDeleteFluid();

  const fluids = useGetFluids();
  const drinks = useGetDrinks();

  //Steps passer ikke rigtigt med hvad der skal ske
  const renderView = () => {
    switch (step) {
      case GuideState.step1:
        return <p>Would you like to delete a drink or a fluid?</p>;
      case GuideState.step2:
        return <p>When done, press "OK"</p>;
      case GuideState.step3:
        return (
          <p>The system will now pump out the fluid from the containers</p>
        );
      case GuideState.step4:
        return (
          <p>
            The system will now show "Finished pumping out" and show what each
            container should contain of fluid
          </p>
        );
      default:
        return <p>Something went wrong :/</p>;
    }
  };

  return (
    <>
      <AlertDialog>
        <AlertDialogTrigger className="py-10 px-16">
          Remove from menu
        </AlertDialogTrigger>
        <AlertDialogContent>
          <AlertDialogHeader>
            <AlertDialogTitle>Delete drink</AlertDialogTitle>
            <AlertDialogDescription>{renderView()}</AlertDialogDescription>
          </AlertDialogHeader>
          <AlertDialogFooter>
            {step !== GuideState.step4 && (
              <Button onClick={handleStep}>Continue</Button>
            )}
            {step === GuideState.step4 && (
              <CustomAlertDialogAction
                onClose={() => setStep(GuideState.step1)}
              >
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

export default DeleteDrinkGuide;

//1. Place the fluid containers under the outlet

//2. When done, press "OK"

//3. The system will now pump out the fluid from the containers

//4 The system will now show "Finished pumping out" and show what each container should contain of fluid

// 1. Systemet viser guide for, hvilke beholdere som skal udskiftes og afventer, at administrator har stillet beholder under udtaget

/* Systemet viser guide for, hvilke beholdere som skal udskiftes og afventer, at administrator har stillet beholder under udtaget 
  
  Administrator stiller beholdere under udtaget 
  
  administrator trykker ”okay” 
  
  Systemet pumper væsken ud af beholdere 
  
  Systemet viser ”færdig med udpumpning” og viser hvad hver beholder skal indeholde af væske 
  
  Systemet afventer administrator fylder væske i beholdere 
  
  Administrator fylder væske i beholdere 
  
  Systemet registrerer beholdernes beholdning og viser ”Sortiment korrekt ændret”  */
