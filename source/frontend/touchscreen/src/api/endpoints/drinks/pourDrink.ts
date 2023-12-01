/** @format */

import { useMutation, useQueryClient } from "@tanstack/react-query";

import http from "../../axios";
//import mocked data
import "@/api/endpoints/drinks/pourDrink.mock";

interface PourDrinkRequest {
  id: number;
}

export interface PourDrinkResponse {}

const pourDrink = async (request: PourDrinkRequest) => {
  return await http.post<PourDrinkResponse>(`v1/drinks/pour/${request.id}`);
};

const usePourDrink = () => {
  const queryClient = useQueryClient();

  return useMutation({
    mutationFn: (request: PourDrinkRequest) => {
      if (!request) {
        return Promise.resolve(null);
      }

      return pourDrink(request);
    },
    mutationKey: ["pourDrink"],
    onSuccess: () => {
      queryClient.invalidateQueries(["getDrinks"]);
    },
  });
};

export default usePourDrink;
