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
import { useEffect, useState } from "react";
import useGetContainers, {
  FluidContainer,
} from "@/api/endpoints/container/getContainers";
import useGetFluids from "@/api/endpoints/fluid/getFluids";
import { Progress } from "@/components/ui/progress";
import CustomAlertDialogAction from "@/components/CustomAlertDialogAction";

enum GuideState {
  step1 = 10,
  step2 = 25,
  step3 = 50,
  step4 = 75,
  step5 = 95,
}

interface ChangeContainerGuideProps {}

function ChangeContainerGuide({}: ChangeContainerGuideProps) {
  const fluids = useGetFluids();
  const getContainers = useGetContainers();
  //I want to do a switch statement on html content so we can have different guides for different steps
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

  //Steps passer ikke rigtigt med hvad der skal ske
  const renderView = () => {
    switch (step) {
      case GuideState.step1:
        return <p>Place a cup under the outlet.</p>;
      case GuideState.step2:
        return <p>Lift the tube out of the fluid in the container.</p>;
      case GuideState.step3:
        return <p> start the pump and wait until liquid stops comimg out.</p>;
      case GuideState.step4:
        return (
          <p>
            {" "}
            Stop the pump and lift the container out to refill it. \n
            container1: {container1.fluid.name} \t container2:
            {container2.fluid.name} \t container3: {container3.fluid.name}
          </p>
        );
      case GuideState.step5:
        return (
          <p>The system is now configured with the new liquids and drinks</p>
        );
      default:
        return <p>Something went wrong :/</p>;
    }
  };

  return (
    <>
      <AlertDialog>
        <AlertDialogTrigger className="py-10 px-16">
          Update menu
        </AlertDialogTrigger>
        <AlertDialogContent>
          <AlertDialogHeader>
            <AlertDialogTitle>Configuration guide</AlertDialogTitle>
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

export default ChangeContainerGuide;

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
