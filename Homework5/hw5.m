close all
clear 


W = randn(2,1000);
Rx = [2 -1.2;-1.2 1];

figure
scatter(W(1,:),W(2,:),2);
xlabel('W_1','FontSize',20);
ylabel('W_2','FontSize',20);

[EVec,Lambda]=eig(Rx);
Xbar=((Lambda)^(1/2))*W;
X=EVec*Xbar;

figure
scatter(Xbar(1,:),Xbar(2,:),2);
xlabel('$\bar{X_1}$','Interpreter','Latex','FontSize',20);
ylabel('$\bar{X_2}$','Interpreter','Latex','FontSize',20);


figure
scatter(X(1,:),X(2,:),2);
xlabel('X_1','FontSize',20);
ylabel('X_2','FontSize',20);



mubar1=(1/length(X(1,:)))*sum(X(1,:));
mubar2=(1/length(X(2,:)))*sum(X(2,:));
Z=zeros(2,1000);
Z(1,:)=X(1,:)-mubar1;
Z(2,:)=X(2,:)-mubar2;

Rbar=(1/length(Z))*Z*Z';

[Evecbar,lambdabar]=eig(Rbar);


X_estim=Evecbar'*X;
W_estim=((lambdabar)^(-1/2))*Evecbar'*X;

figure
scatter(W_estim(1,:),W_estim(2,:),2);
xlabel('W^{est}_1','FontSize',20);
ylabel('W^{est}_2','FontSize',20);

figure
scatter(X_estim(1,:),X_estim(2,:),2);
xlabel('X^{est}_1','FontSize',20);
ylabel('X^{est}_2','FontSize',20);


read_data;

newmu = mean(X,2);
[r,c] = size(X);
Z = zeros(r,c);
Z = (1/sqrt(n-1))*(bsxfun(@minus,X,mu_hat));
[U S V] = svd(Z,0);

for k=1:12
  img=reshape(U(:,k),64,64);
  figure; subplot(4,3,k); imagesc(img);
  axis('image'); colormap(gray(256));
  title(strcat('eigenvalue',num2str(k)),'Interpreter','none');
end

Y = U'*(bsxfun(@minus,X,mu_hat));
figure;
for k = 1:4
	plot(1:10,Y(1:10,k));
	hold on;
end
legend('a','b','c','d');
xlabel('Eigenvector number');
ylabel('Projection value');

img = reshape(X(:,1),64,64);
figure;
imagesc(img);
axis('image'); colormap(gray(256));

m = 1;
for k = [1 5 10 15 20 30]
	Xtmp = U(:,1:k)*Y(1:k,:);
	Xest = bsxfun(@plus,Xtmp,mu_hat);
	img = reshape(Xest(:,1),64,64);
	figure; subplot(3,2,m); image(img);
	title(strcat('"a" from ',num2str(k),' eigenvectors'));
	axis('image'); colormap(gray(256));
	m = m+1;
end


