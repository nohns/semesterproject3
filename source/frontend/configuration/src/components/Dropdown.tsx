/** @format */

import { useState } from "react";
import {
  DropdownMenu,
  DropdownMenuTrigger,
  DropdownMenuContent,
  DropdownMenuRadioGroup,
  DropdownMenuRadioItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
} from "@/components/ui/dropdown-menu";

import { Button } from "@/components/ui/button";
import { Fluid } from "@/api/endpoints/fluid/getFluids";

interface CustomDropdownProps {
  container: Fluid;
  setContainer: React.Dispatch<React.SetStateAction<Fluid>>;
  fluids: Fluid[];
  className?: string;
}

function CustomDropdown({
  container,
  setContainer,
  fluids,
  className,
}: CustomDropdownProps) {
  //const [drinks, setDrinks] = useState("Vælg drink");

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild className={className}>
        <Button>{container.name}</Button>
      </DropdownMenuTrigger>
      <DropdownMenuContent>
        <DropdownMenuLabel>Drinks</DropdownMenuLabel>
        <DropdownMenuSeparator />
        <DropdownMenuRadioGroup
          value={container.name}
          onValueChange={(value) => {
            const selectedFluid = fluids.find((fluid) => fluid.name === value);
            if (selectedFluid) {
              setContainer(selectedFluid);
            }
          }}
        >
          {fluids.map((fluid) => (
            <DropdownMenuRadioItem key={fluid.name} value={fluid.name}>
              {fluid.name}
            </DropdownMenuRadioItem>
          ))}
        </DropdownMenuRadioGroup>
      </DropdownMenuContent>
    </DropdownMenu>
  );
}

export default CustomDropdown;
