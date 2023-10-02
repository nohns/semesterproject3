/** @format */
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";

const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      retry: false,
      staleTime: 1000 * 60 * 5,

      onError: (error) => {
        console.log(error);
        return error;
      },
    },
  },
});

interface Props {
  children: React.ReactNode;
}

const ReactQueryClientProvider: React.FC<Props> = ({ children }) => {
  return (
    <QueryClientProvider client={queryClient} contextSharing={false}>
      {children}
    </QueryClientProvider>
  );
};

export default ReactQueryClientProvider;
