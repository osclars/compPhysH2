
energy = load('../savedData/alfaCompare.data');
errorbar(energy(:,1), energy(:,2), energy(:,3));

grid on
%axis([0,32,650,900]);
set(gca,'fontsize',16);
xlabel('Value of alpha','fontsize',16)
ylabel('Energy [a.u.]','fontsize',16)

