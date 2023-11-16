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

function CustomDropdown({ className }: { className?: string }) {
  const [drinks, setDrinks] = useState("Vælg drink");

  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild className={className}>
        <Button>{drinks}</Button>
      </DropdownMenuTrigger>
      <DropdownMenuContent>
        <DropdownMenuLabel>Drinks</DropdownMenuLabel>
        <DropdownMenuSeparator />
        <DropdownMenuRadioGroup value={drinks} onValueChange={setDrinks}>
          <DropdownMenuRadioItem value="Vodka">Vodka</DropdownMenuRadioItem>
          <DropdownMenuRadioItem value="Gin">Gin</DropdownMenuRadioItem>

          <DropdownMenuSeparator />

          <DropdownMenuRadioItem value="Appelsin Juice">
            Appelsin Juice
          </DropdownMenuRadioItem>
          <DropdownMenuRadioItem value="Coca Cola">
            Coca Cola
          </DropdownMenuRadioItem>
          <DropdownMenuRadioItem value="Blå Booster">
            Blå Booster
          </DropdownMenuRadioItem>
        </DropdownMenuRadioGroup>
      </DropdownMenuContent>
    </DropdownMenu>
  );
}

export default CustomDropdown;
