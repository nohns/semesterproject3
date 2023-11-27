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

import useGetDrinks from "@/api/endpoints/drinks/getDrinks";

enum GuideState {
  step1 = 50,
  step2 = 99,
}

interface DeleteDrinkGuideProps {}

function DeleteDrinkGuide({}: DeleteDrinkGuideProps) {
  //I want to do a switch statement on html content so we can have different guides for different steps

  const [step, setStep] = useState<GuideState>(GuideState.step1);

  const deleteDrink = useDeleteDrink();

  const drinks = useGetDrinks();

  //Steps passer ikke rigtigt med hvad der skal ske
  const renderView = () => {
    switch (step) {
      case GuideState.step1:
        return (
          <div>
            <div>Which drink would you like to delete?</div>
            <div className="flex flex-row gap-4 my-2">
              {drinks.data?.drinks.map((drink) => (
                <Button
                  onClick={() => {
                    deleteDrink.mutate({ id: drink.id! });
                    setStep(GuideState.step2);
                  }}
                >
                  {drink.name}
                </Button>
              ))}
            </div>
          </div>
        );
      case GuideState.step2:
        return <p>Succesfully deleted the requested data</p>;
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
            <AlertDialogTitle>Remove from menu</AlertDialogTitle>
            <AlertDialogDescription>{renderView()}</AlertDialogDescription>
          </AlertDialogHeader>
          <AlertDialogFooter>
            {step === GuideState.step2 && (
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
