/** @format */

import { Button } from "@/components/ui/button";
import React from "react";

interface CreateDrinkButtonProps {
  createDrink: () => void;
}

function CreateDrinkButton({ createDrink }: CreateDrinkButtonProps) {
  return (
    <>
      <div>
        <Button onClick={createDrink}>Create Drink</Button>
      </div>
    </>
  );
}

export default CreateDrinkButton;
